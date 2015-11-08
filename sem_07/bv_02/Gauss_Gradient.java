import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.FloatProcessor;
import ij.process.ImageProcessor;

public class Gauss_Gradient implements PlugInFilter {

	@Override
	public int setup(String arg0, ImagePlus arg1) {
		return DOES_RGB + DOES_8G + NO_UNDO + NO_CHANGES;
	}

	@Override
	public void run(ImageProcessor ip) {
		GenericDialog gd;
		FloatProcessor original;
		FloatProcessor fp_gaus_x;
		FloatProcessor fp_gaus_y;
		FloatProcessor fp_gaus_mag;
		float gaus_x_tmp[];
		float gaus_y_tmp[];
		ImagePlus ip_gaus_x;
		ImagePlus ip_gaus_y;
		ImagePlus ip_gaus_mag;
		long time;
		int i;
		float sigma;
		int width;
		int height;
		float gaus_filter[][];
		int filter_size;

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
		gaus_x_tmp = new float[width * height];
		gaus_y_tmp = new float[width * height];

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

		System.out.printf("time gaus x + y: %fs\n",
				(System.currentTimeMillis() - time) / 1000.f);

		calculate_mag((float [])fp_gaus_mag.getPixels(),
				(float [])fp_gaus_x.getPixels(),
				(float [])fp_gaus_y.getPixels(),
				width * height);
		System.out.printf("time gaus x + y + mag: %fs\n",
				(System.currentTimeMillis() - time) / 1000.f);

		ip_gaus_x = new ImagePlus("gaus_x", fp_gaus_x);
		ip_gaus_y = new ImagePlus("gaus_y", fp_gaus_y);
		ip_gaus_mag = new ImagePlus("gaus_mag", fp_gaus_mag);

		ip_gaus_x.show();
		ip_gaus_y.show();
		ip_gaus_mag.show();
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
