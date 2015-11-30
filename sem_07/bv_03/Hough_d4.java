import java.awt.Color;
import java.awt.Polygon;

import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.gui.Overlay;
import ij.gui.PolygonRoi;
import ij.gui.Roi;
import ij.plugin.filter.PlugInFilter;
import ij.process.ByteProcessor;
import ij.process.FloatProcessor;
import ij.process.ImageProcessor;

public class Hough_d4 implements PlugInFilter {

	@Override
	public int setup(String arg0, ImagePlus arg1) {
		return DOES_RGB + DOES_8G + NO_UNDO + NO_CHANGES;
	}

	@Override
	public void run(ImageProcessor ip) {
		GenericDialog gd;
		ImageProcessor gray_image;
		FloatProcessor original;
		FloatProcessor fp_gaus_x;
		FloatProcessor fp_gaus_y;
		FloatProcessor fp_gaus_mag;
		FloatProcessor fp_nms;
		ByteProcessor bp_as;
		float gaus_x_tmp[];
		float gaus_y_tmp[];
		ImagePlus ip_gaus_x;
		ImagePlus ip_gaus_y;
		ImagePlus ip_gaus_mag;
		ImagePlus ip_nms;
		ImagePlus ip_as;
		ImagePlus ip_final;
		long time;
		int i;
		float sigma;
		int width;
		int height;
		float gaus_filter[][];
		int filter_size;
		int darkest_pixel[];
		int inner_circle[];
		int outter_circle[];
		int block_size = 43;

		sigma = 3.0f;

		gd = new GenericDialog("Magic!");
		gd.addNumericField("Sigma: ", 1.0f, 0);
		gd.showDialog();
		if (gd.wasCanceled()) {
			return;
		}
		sigma = (int)gd.getNextNumber();

		filter_size = 2 * (int)Math.ceil(2.0f * sigma) + 1;
		gaus_filter = new float[2][filter_size];
		for (i = 0; i < filter_size; i++) {
			gaus_filter[0][i] = get_gaussian_x(sigma, (float)(i - (filter_size / 2)));
			gaus_filter[1][i] = get_gaussian_y(sigma, (float)(i - (filter_size / 2)));
		}

		print_gaus_filter(gaus_filter, filter_size);

		width = ip.getWidth();
		height = ip.getHeight();

		original = ip.convertToFloatProcessor();
		fp_gaus_x = new FloatProcessor(width, height);
		fp_gaus_y = new FloatProcessor(width, height);
		fp_gaus_mag = new FloatProcessor(width, height);
		fp_nms = new FloatProcessor(width, height);
		bp_as = new ByteProcessor(width, height);
		gaus_x_tmp = new float[width * height];
		gaus_y_tmp = new float[width * height];

		if (ip.isGrayscale()) {
			gray_image = ip;
		} else {
			gray_image = get_gray_image(ip);
		}

		time = System.currentTimeMillis();

		calculate_gaus_x(gaus_x_tmp,
				(float [])original.getPixels(),
				width, height,
				gaus_filter[0], filter_size);

		calculate_gaus_y((float [])fp_gaus_x.getPixels(),
				gaus_x_tmp,
				width, height,
				gaus_filter[1], filter_size);

		System.out.printf("time gaus x: %fs\n",
				(System.currentTimeMillis() - time) / 1000.f);

		calculate_gaus_y(gaus_y_tmp,
				(float [])original.getPixels(),
				width, height,
				gaus_filter[0], filter_size);

		calculate_gaus_x((float [])fp_gaus_y.getPixels(),
				gaus_y_tmp,
				width, height,
				gaus_filter[1], filter_size);

		System.out.printf("time + gaus y: %fs\n",
				(System.currentTimeMillis() - time) / 1000.f);

		calculate_mag((float [])fp_gaus_mag.getPixels(),
				(float [])fp_gaus_x.getPixels(),
				(float [])fp_gaus_y.getPixels(),
				width * height);
		System.out.printf("time + mag: %fs\n",
				(System.currentTimeMillis() - time) / 1000.f);

		calculate_nms((float[])fp_nms.getPixels(),
				(float [])fp_gaus_mag.getPixels(),
				(float [])fp_gaus_x.getPixels(),
				(float [])fp_gaus_y.getPixels(),
				width, height);
		System.out.printf("time + nms: %fs\n",
				(System.currentTimeMillis() - time) / 1000.f);

		calculate_as((byte[])bp_as.getPixels(),
				(float [])fp_nms.getPixels(),
				width, height);
		System.out.printf("time + as: %fs\n",
				(System.currentTimeMillis() - time) / 1000.f);

		darkest_pixel = get_darkest_pixel((byte[])gray_image.getPixels(), width,
				height, block_size);
		System.out.printf("Darkest Pixel: (%d/%d)\n",
				darkest_pixel[0],
				darkest_pixel[1]);
		System.out.printf("time + darkest pixel: %fs\n",
				(System.currentTimeMillis() - time) / 1000.f);

		// inner_circle = get_circle_ido((byte[])bp_as.getPixels(), width, height,
		// 	darkest_pixel[0] - block_size / 2,
		// 	darkest_pixel[1] - block_size / 2, block_size, 15, 41);
		// System.out.printf("time + inner circle: %fs\n",
		// 		(System.currentTimeMillis() - time) / 1000.f);

		// outter_circle = get_circle_ido((byte[])bp_as.getPixels(), width, height,
		// 	inner_circle[0] - 1, inner_circle[1] - 1, 3,
		// 	inner_circle[2] + 20, 140);
		// System.out.printf("time + outter circle: %fs\n",
		// 		(System.currentTimeMillis() - time) / 1000.f);

		inner_circle = get_circle_hough((byte[])bp_as.getPixels(), width, height,
			darkest_pixel[0] - block_size / 2,
			darkest_pixel[1] - block_size / 2, block_size, 15, 41);
		System.out.printf("time + inner circle: %fs\n",
				(System.currentTimeMillis() - time) / 1000.f);

		// outter_circle = get_circle_hough((byte[])bp_as.getPixels(), width, height,
		// 	inner_circle[0] - 1, inner_circle[1] - 1, 3,
		// 	inner_circle[2] + 20, 140);
		// System.out.printf("time + outter circle: %fs\n",
		// 		(System.currentTimeMillis() - time) / 1000.f);

		ip.setColor(Color.RED);
		ip.drawRect(darkest_pixel[0] - block_size / 2,
					darkest_pixel[1] - block_size / 2,
					block_size, block_size);
		ip.drawOval(inner_circle[0] - inner_circle[2],
				inner_circle[1] - inner_circle[2], inner_circle[2] * 2,
				inner_circle[2] * 2);
		// ip.drawOval(outter_circle[0] - outter_circle[2],
		// 		outter_circle[1] - outter_circle[2], outter_circle[2] * 2,
		// 		outter_circle[2] * 2);

		System.out.printf("Inner Circle: (%d/%d)|%d : %d\n",
				inner_circle[0], inner_circle[1],
				inner_circle[2], inner_circle[3]);

		// System.out.printf("Outter Circle: (%d/%d)|%d : %d\n",
		// 		outter_circle[0], outter_circle[1],
		// 		outter_circle[2], outter_circle[3]);

		ip_gaus_x = new ImagePlus("gaus_x", fp_gaus_x);
		ip_gaus_y = new ImagePlus("gaus_y", fp_gaus_y);
		ip_gaus_mag = new ImagePlus("gaus_mag", fp_gaus_mag);
		ip_nms = new ImagePlus("nms", fp_nms);
		ip_as = new ImagePlus("as", bp_as);
		ip_final = new ImagePlus("final", ip);

		ip_gaus_x.show();
		ip_gaus_y.show();
		ip_gaus_mag.show();
		ip_nms.show();
		ip_as.show();
		ip_final.show();
	}

	private void calculate_as(byte[] result, float[] nms, int width,
			int height) {

		int block_size = 8; // 1 / block_size
		float c = 0.08f;

		float [][]asb;
		float avg;
		int rw; // radius width
		int rh; // radius height
		int rw_tmp; // radius width tmp
		int rh_tmp; // radius height tmp
		int cr; // current row
		int cc; // current column
		int cp; // curren position
		float mod_c; // 1.0f - c

		rw = (width  / block_size) >> 1;
		rh = (height / block_size) >> 1;
		mod_c = 1.0f - c;

		asb = get_asb_float(nms, width, height);

		for (cr = 0; cr < height; cr++) {
			/* top / bottom */
			if (cr < rh) {
				rh_tmp = cr;
			} else if (cr + rh >= height) {
				rh_tmp = rh - (cr + rh - (height - 1));
			} else {
				rh_tmp = rh;
			}

			for (cc = 0; cc < width; cc++) {
				/* left / rigth */
				if (cc < rw) {
					rw_tmp = cc;
				} else if (cc + rw >= width) {
					rw_tmp = rw - (cc + rw - (width - 1));
				} else {
					rw_tmp = rw;
				}

				cp = cr * width + cc;
				avg = (asb[cr + rh_tmp][cc + rw_tmp]
						+ asb[cr - rh_tmp][cc - rw_tmp])
					  - (asb[cr + rh_tmp][cc - rw_tmp]
						+ asb[cr - rh_tmp][cc + rw_tmp]);
				avg = avg / (rh_tmp * rw_tmp);
				if (nms[cp] < mod_c * avg) {
					result[cp] = 0;
				} else {
					result[cp] = -128;
				}
			}
		}
	}

	private int[] get_circle_hough(byte[] pix, int width, int height, int x, int y,
			int block_size, int min_rad, int max_rad) {
		int hough_data[][][] = new int[block_size][block_size][max_rad - min_rad];
		int c_x; // currenct x
		int c_y; // current y
		int c_i_x;
		int c_i_y;
		int c_rad; // current rad
		int dist;

		for (c_x = x - block_size; c_x < x + block_size * 2; c_x++) {
			for (c_y = y - block_size; c_y < y + block_size * 2; c_y++) {
				if (c_y < 0 || c_y >= height || c_x < 0 || c_x >= width) {
					continue;
				}
				if (pix[c_y * width + c_x] != -128) {
					continue;
				}
				for (c_i_x = x; c_i_x < x + block_size; c_i_x++) {
					for (c_i_y = y; c_i_y < y + block_size; c_i_y++) {
						dist = (int)(Math.sqrt(((c_i_x - c_x) * (c_i_x - c_x)) + ((c_i_y - c_y) * (c_i_y - c_y))) + 0.5);
						if (dist >= min_rad && dist < max_rad) {
							hough_data[c_i_x - x][c_i_y - y][dist - min_rad] += 1;
						}
					}
				}
			}
		}

		/* find the best */
		int best[] = {
			0, // best x
			0, // best y
			0, // best rad
			0  // best val
		};

		for (c_x = 0; c_x < block_size; c_x++) {
			for (c_y = 0; c_y < block_size; c_y++) {
				for (c_rad = 0; c_rad < max_rad - min_rad; c_rad++) {
					if (hough_data[c_x][c_y][c_rad] > best[3]) {
						best[0] = c_x + x;
						best[1] = c_y + y;
						best[2] = c_rad + min_rad;
						best[3] = hough_data[c_x][c_y][c_rad];
					}
					if (c_rad + 15 == 33) {
						System.out.printf("Found a better one! %d/%d/%d/%d\n",
								c_x + (x - block_size),
								c_y + (y - block_size),
								c_rad + min_rad,
								hough_data[c_x][c_y][c_rad]);
					}
				}
			}
		}

		return best;
	}

	private int[] get_circle_ido(byte[] pix, int width, int height, int x, int y,
			int block_size, int min_rad, int max_rad) {
		int jump;
		int size;

		int cp; // current position
		int c_x; // currenct x
		int c_y; // current y
		int c_rad; // current rad
		int cur_val; // current val
		float cur_avg; // current avg

		int best[] = {
			0, // best x
			0, // best y
			0, // best rad
			0  // best val
		};
		float best_avg = 0.0f; // best avg

		int count;
		int x_off = 0; // x offset
		int y_off = 0; // y offset

		size = width * height;

		for (c_x = x; c_x < x + block_size; c_x++) {
			for (c_y = y; c_y < y + block_size; c_y++) {
				cp = c_y * width + c_x;
				for (c_rad = min_rad; c_rad < max_rad; c_rad++) {
					if (cp + (c_rad * width) > size
							|| cp - (c_rad * width) < 0) {
						break;
					}
					x_off = c_rad;
					y_off = 0;
					cur_val = 0;
					jump = 1 - x_off;
					count = 0;
					while (y_off <= x_off) {
						if (pix[cp + (y_off * width) + x_off] == -128) { cur_val++; } // right bottom
						if (pix[cp - (y_off * width) + x_off] == -128) { cur_val++; } // right top
						if (pix[cp + (y_off * width) - x_off] == -128) { cur_val++; } // left bottom
						if (pix[cp - (y_off * width) - x_off] == -128) { cur_val++; } // left top
						if (pix[cp + (x_off * width) + y_off] == -128) { cur_val++; } // bottom right
						if (pix[cp + (x_off * width) - y_off] == -128) { cur_val++; } // bottom left
						if (pix[cp - (x_off * width) + y_off] == -128) { cur_val++; } // top right
						if (pix[cp - (x_off * width) - y_off] == -128) { cur_val++; } // top left
						y_off++;
						if (jump <= 0) {
							jump += 2 * y_off + 1;
						} else {
							x_off--;
							jump += 2 * (y_off - x_off) + 1;
						}
						count += 8;
					}
					cur_avg = (float)cur_val / (float)count;
					if (cur_avg > best_avg) {
						best_avg = cur_avg;
						best[0] = c_x;
						best[1] = c_y;
						best[2] = c_rad;
						best[3] = cur_val;
					}
				}
			}
		}

		return best;
	}

	static void calculate_nms(float[] result, float[] mag, float[] x, float[] y,
			int width, int heigth) {
		int cr;
		int cc;
		int cp;

		for (cr  = 1; cr < heigth - 1; cr++) {
			for (cc  = 1; cc < width - 1; cc++) {
				cp = cr * width + cc;
				switch (quantizeDirection(x[cp], y[cp])) {
					case 0:
						break;
					case 1:
						if (mag[cp] < mag[cp - width] || mag[cp] < mag[cp + width]) {
							result[cp] = 0.0f;
						} else {
							result[cp] = mag[cp];
						}
						break;
					case 2:
						if (mag[cp] < mag[cp - width + 1] || mag[cp] < mag[cp + width - 1]) {
							result[cp] = 0.0f;
						} else {
							result[cp] = mag[cp];
						}
						break;
					case 3:
						if (mag[cp] < mag[cp - 1] || mag[cp] < mag[cp + 1]) {
							result[cp] = 0.0f;
						} else {
							result[cp] = mag[cp];
						}
						break;
					case 4:
						if (mag[cp] < mag[cp - width - 1] || mag[cp] < mag[cp + width + 1]) {
							result[cp] = 0.0f;
						} else {
							result[cp] = mag[cp];
						}
						break;
				}
			}
		}
	}

	static float TAN_PI_1_8 = 0.41421356237f;
	static float TAN_PI_3_8 = 2.41421356237f;
	//**********************************************************************
	// directions are quantized into only 4+1 bins:
	// 0 = invalid, 1 = horizontal, 2 = diagonal_1, 3 = vertical, 4 = diagonal_2 (left up)
	static int quantizeDirection(float dir_x, float dir_y)
	{
		if (dir_x == 0.0f)
			if (dir_y == 0.0f)
				return 0;
			else
				return 1;  // horizontal
		else
		{
			// alpha = Math.atan(pixels_y[k] / pixels_x[k]);  // -Pi/2 < alpha < Pi/2
			float tan_alpha = dir_y / dir_x;  //  -\infty < tan_alpha < \infty
			if (tan_alpha > TAN_PI_3_8)
				return 1;  // horizontal
			else if (tan_alpha >  TAN_PI_1_8)
				return 4;  // diagonal_1 (right up)
			else if (tan_alpha > -TAN_PI_1_8)
				return 3;  // vertical
			else if (tan_alpha > -TAN_PI_3_8)
				return 2;  // diagonal_2 (left up)
			else
				return 1;  // horizontal
		}
	}

	private Overlay get_block_overlay(int x, int y, int block_size) {
		Polygon poly;
		Roi roi;
		int rad;

		rad = block_size / 2;
		poly = new Polygon();

		poly.addPoint(x - rad, y - rad);
		poly.addPoint(x + rad, y - rad);
		poly.addPoint(x + rad, y + rad);
		poly.addPoint(x - rad, y + rad);
		poly.addPoint(x - rad, y - rad);

		roi = new PolygonRoi(poly, Roi.POLYLINE);
		roi.setStrokeColor(Color.RED);
		roi.setStrokeWidth(1);

		return new Overlay(roi);
	}

	private int[] get_darkest_pixel(byte[] pixels, int width, int heigth,
			int block_size) {
		long[][] ASB;
		int darkest[];
		int cur_row;
		int cur_col;
		int rad;
		long cur_black;
		long cur_darkest;

		darkest = new int[2];
		cur_darkest = 2164000000l;
		rad = block_size / 2;
		ASB = get_ASB(pixels, width, heigth);

		for (cur_row = rad + 1; cur_row < heigth - rad; cur_row++) {
			for (cur_col = rad + 1; cur_col < width - rad; cur_col++) {
				cur_black = (ASB[cur_row + rad][cur_col + rad]
								+ ASB[cur_row - (rad + 1)][cur_col - (rad + 1)])
						  - (ASB[cur_row + rad][cur_col - (rad + 1)]
								+ ASB[cur_row - (rad + 1)][cur_col + rad]);
				if (cur_darkest >= cur_black) {
					cur_darkest = cur_black;
					darkest[1] = cur_row;
					darkest[0] = cur_col;
				}
			}
		}
		return darkest;
	}

	private ImageProcessor get_gray_image(ImageProcessor ip) {
		ImageProcessor ip_gray;
		int[] rgb_pixels;
		byte[] gray_pixels;
		int i, r, g, b;

		ip_gray = new ByteProcessor(ip.getWidth(), ip.getHeight());
		rgb_pixels = (int[]) ip.getPixels();
		gray_pixels = (byte[]) ip_gray.getPixels();

		for (i = 0; i < rgb_pixels.length; i++) {
			r = (rgb_pixels[i] & 0xff0000) >> 16;
			g = (rgb_pixels[i] & 0x00ff00) >>  8;
			b = (rgb_pixels[i] & 0x0000ff);
			gray_pixels[i] = (byte) (0.299*r + 0.587*g + 0.114*b + 0.5);
		}

		return ip_gray;
	}

	private float[][] get_asb_float(float[] gray_pixels, int width, int heigth) {
		long sum_row;
		int cur_row;
		int cur_col;
		float[][] asb;

		asb = new float[heigth][width];
		for (cur_col = 0, sum_row = 0; cur_col < width; cur_col++) {
			sum_row += gray_pixels[cur_col];
			asb[0][cur_col] = sum_row;
		}

		for (cur_row = 1; cur_row < heigth; cur_row++) {
			for (cur_col = 0, sum_row = 0; cur_col < width; cur_col++) {
				sum_row += gray_pixels[(cur_row * width) + cur_col];
				asb[cur_row][cur_col] = sum_row + asb[cur_row - 1][cur_col];
			}
		}

		return asb;
	}

	private long[][] get_ASB(byte[] gray_pixels, int width, int heigth) {
		long sum_row;
		int cur_row;
		int cur_col;
		long[][] ASB;

		ASB = new long[heigth][width];
		for (cur_col = 0, sum_row = 0; cur_col < width; cur_col++) {
			sum_row += gray_pixels[cur_col] & 0xff;
			ASB[0][cur_col] = sum_row;
		}

		for (cur_row = 1; cur_row < heigth; cur_row++) {
			for (cur_col = 0, sum_row = 0; cur_col < width; cur_col++) {
				sum_row += gray_pixels[(cur_row * width) + cur_col] & 0xff;
				ASB[cur_row][cur_col] = sum_row + ASB[cur_row - 1][cur_col];
			}
		}

		return ASB;
	}

	private void calculate_mag(float[] result, float[] x, float[] y, int size) {
		for (int i = 0; i < size; i++) {
			result[i] = (float) Math.sqrt(x[i] * x[i] + y[i] * y[i]);
		}
	}

	private void calculate_gaus_x(float result[], float data[], int w,
			int h, float gaus_filter[], int size) {
		int cr; // current row
		int cc; // current column
		int cec; // current extra column
		int cg; // current gauss position
		int rad;
		float s; // sums
		int cp; // current position

		rad = size / 2;

		// rows
		for (cr = 0; cr < h; cr++) {
			// sides
			for (cec = 0; cec < rad; cec++) {
				// left side
				cp = cr * w + cec;
				s = 0.0f;
				// mirrored
				for (cg = 0; cg < (rad - cec); cg++) {
					s += gaus_filter[cg]
						* data[cp + (cg - rad) + 2 * (rad - cg - cec)];
				}
				// not mirrored
				for (; cg < size; cg++) {
					s += gaus_filter[cg] * data[cp + (cg - rad)];
				}
				result[cp] = s;

				// right side
				cp = cr * w + cec + (w - rad);
				s = 0.0f;
				// not mirrored
				for (cg = 0; cg < size - (cec + 1); cg++) {
					s += gaus_filter[cg] * data[cp + (cg - rad)];
				}
				// mirrored
				for (; cg < size; cg++) {
					s += gaus_filter[cg]
						* data[cp + (cg - rad) - 2 * (cg - (size - (cec + 2)))];
				}
				result[cp] = s;
			}
			// rest
			for (cc = rad; cc < w - rad; cc++) {
				cp = cr * w + cc;
				s = 0.0f;
				for (cg = 0; cg < size; cg++) {
					s += gaus_filter[cg] * data[cp + cg - rad];
				}
				result[cp] = s;
			}
		}
	}

	private void calculate_gaus_y(float result[], float data[], int w,
			int h, float gaus_filter[], int size) {
		int cr; // current row
		int cc; // current column
		int cer; // current extra column
		int cg; // current gauss position
		int rad;
		float s; // sums
		int cp; // current position

		rad = size / 2;

		// columns
		for (cc = 0; cc < w; cc++) {
			// top and bottom
			for (cer = 0; cer < rad; cer++) {
				// top side
				cp = cc + cer * w;
				s = 0.0f;
				// mirrored
				for (cg = 0; cg < (rad - cer); cg++) {
					s += gaus_filter[cg]
						* data[cp + ((cg - rad) * w) + (2 * (rad - cg - cer) * w)];
				}
				// not mirrored
				for (; cg < size; cg++) {
					s += gaus_filter[cg] * data[cp + ((cg - rad) * w)];
				}
				result[cp] = s;

				// bottom side
				cp = cc + cer * w + (h - rad) * w;
				s = 0.0f;
				// not mirrored
				for (cg = 0; cg < size - (cer + 1); cg++) {
					s += gaus_filter[cg]
						* data[cp + ((cg - rad) * w)];
				}
				// mirrored
				for (; cg < size; cg++) {
					s += gaus_filter[cg]
						* data[cp + ((cg - rad) * w) - (2 * (cg - (size - (cer + 2))) * w)];
				}
				result[cp] = s;
			}
			// rest
			for (cr = rad; cr < h - rad; cr++) {
				cp = cr * w + cc;
				s = 0.0f;
				for (cg = 0; cg < size; cg++) {
					s += gaus_filter[cg] * data[cp + ((cg - rad) * w)];
				}
				result[cp] = s;
			}
		}
	}

	private void print_gaus_filter(float[][]gaus_filter, int filter_size) {
		int i;

		System.out.printf("gaus_filter_x: [");
		for (i = 0; i < filter_size; i++) {
			System.out.printf(" %f", gaus_filter[0][i]);
		}
		System.out.printf("]\n");

		System.out.printf("gaus_filter_y: [");
		for (i = 0; i < filter_size; i++) {
			System.out.printf(" %f", gaus_filter[1][i]);
		}
		System.out.printf("]\n");
	}

	private float get_gaussian_x(float sigma, float offset) {
		float result;

		result = -offset / (sigma * sigma);
		result *= _get_gaussian_val(sigma, offset);

		return result;
	}

	private float get_gaussian_y(float sigma, float offset) {
		return _get_gaussian_val(sigma, offset);
	}

	private float _get_gaussian_val(float sigma, float offset) {
		float result;

		result =  (1.0f / (float)Math.sqrt(2.0f * (float)Math.PI * sigma));
		result *= (float) Math.exp(-(offset * offset) / (2.0f * (sigma * sigma)));

		return result;
	}
}
