import java.awt.Color;
import java.awt.Polygon;

import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.gui.Overlay;
import ij.gui.PolygonRoi;
import ij.gui.Roi;
import ij.plugin.filter.PlugInFilter;
import ij.process.ByteProcessor;
import ij.process.ImageProcessor;

public class Darkest_Pixel implements PlugInFilter {

	@Override
	public int setup(String arg0, ImagePlus arg1) {
		return DOES_RGB + NO_UNDO + NO_CHANGES;
	}

	@Override
	public void run(ImageProcessor ip) {
		int block_size;
		GenericDialog gd;
		ImagePlus grayImage;
		ImageProcessor ip_gray;
		long time;
		int darkest[];

		ip_gray = get_gray_image(ip);
		grayImage = new ImagePlus("Gray Image", ip_gray);
		block_size = 19;

		gd = new GenericDialog("Magic!");
		gd.addNumericField("Block Size: ", block_size, 0);
		gd.showDialog();
		if (gd.wasCanceled()) {
			return;
		}

		block_size = (int)gd.getNextNumber();

		time = System.currentTimeMillis();
		darkest = get_darkest_pixel((byte [])ip_gray.getPixels(),
									ip_gray.getWidth(),
									ip_gray.getHeight(),
									block_size);
		System.out.print("time: "
				+ ((System.currentTimeMillis() - time) / 1000.f) + "s\n");
		grayImage.setOverlay(get_block_overlay(darkest[0], darkest[1],
				block_size));
		grayImage.show();

		System.out.print("pixel (x/y): ("
				+ darkest[0] + "/"
				+ darkest[1] + ")\n\n");
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

		System.out.print("asb: " + ASB[darkest[1]][darkest[0]]
				+ ", block only: " + cur_darkest
				+ ", avg: " + ((cur_darkest + 0.5f)
								/ (float)(block_size * block_size))
				+ "\n");

		return darkest;
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
}
