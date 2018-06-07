import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class MandelbrotCompute {
	
	private int width;
	private int height;
	private int threadCount;
	private BufferedImage image;
	private String file;
	private double[] coordinates;
	private boolean quiet;
	
	public MandelbrotCompute(int width, int height, int threads, String file, double[] coords, boolean quiet) {
		
		this.width = width;
		this.height = height;
		this.threadCount = threads;
		this.image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		this.file = new String(file);
		this.coordinates = coords;
		this.quiet = quiet;
	}
	
	public void Mendelbrot() throws IOException {
	
		long startTimer = System.currentTimeMillis();
		
		int chunkSize = width / threadCount;
		Thread tr[] = new Thread[threadCount];
		
		for(int i = 0; i < threadCount; i++) {
	
			MandelbrotRunnable r = new MandelbrotRunnable(width, height, image, chunkSize, i, threadCount, coordinates, quiet);
			Thread t = new Thread(r);
			tr[i] = t;
			t.start();
		}
		
		for(int i = 0; i < threadCount; i++) {
			try {
				tr[i].join();
			} 
			catch (InterruptedException e) {
			}
		}
		
		ImageIO.write(image, "png", new File(file));
		System.out.println("Total execution time for current run (millis): " + (System.currentTimeMillis() - startTimer));
		System.out.println("Threads used in current run: " + threadCount);
	}
}


