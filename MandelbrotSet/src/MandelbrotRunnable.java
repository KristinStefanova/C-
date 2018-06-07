import java.awt.Color;
import java.awt.image.BufferedImage;

import org.apache.commons.math3.analysis.function.Cos;
import org.apache.commons.math3.complex.Complex;

public class MandelbrotRunnable implements Runnable {
	
	private final static int MAX_ITERATIONS = 800;
	
	private int width;
	private int height;
	private BufferedImage image;
	private int chunk_size; 
	private int indexOfThread; // thread sequence number 
	private int thread_count; // number of threads
	private boolean quiet;
	private double[] coords;
	
	public MandelbrotRunnable(int width, int height, BufferedImage image, int chunk_size, int index, int thread_count, double[] limits, boolean quiet) {
		
		this.width = width;
		this.height = height;
		this.image = image;
		this.chunk_size = chunk_size;
		this.indexOfThread = index;
		this.thread_count = thread_count;	
		this.quiet = quiet;
		this.coords = limits;
	}
	
	public static Complex applyFunction (Complex c, Complex z){
		
		double a = Math.exp((-1) * z.getReal());
		double b = Math.cos((-1) * z.getImaginary());
		double d = Math.sin((-1) * z.getImaginary());
		Complex m = new Complex(b, d);		
		
		return  c.multiply(m.multiply(a)).add(z.multiply(z));
	}	
	
	public void run() {
		
		long startTimer = System.currentTimeMillis();
		if(quiet != false)
		{	
			System.out.println("Thread-<" + indexOfThread + "> started.");
		}
		
		int chunckStart = indexOfThread * chunk_size;
		int chunckEnd = (indexOfThread + 1) * chunk_size;
		if (indexOfThread == (thread_count - 1)) 
			chunckEnd = width - 1;
		
		double zx = 0;
		double zy = 0;
		double re = (coords[1] - coords[0]) / image.getWidth();
		double im = (coords[3] - coords[2]) / image.getHeight();	
			
		int k = 0;
		for (int i = chunckStart; i < chunckEnd; i++) {
			zx = coords[0] + i * re; 
			for (int j = 0; j < image.getHeight(); j++) {
				zy = coords[3] - j * im;
				
				Complex z = new Complex(0, 0);
				Complex c = new Complex(zx, zy);
								
				for (k = 0; k < MAX_ITERATIONS; k++) {
					if (z.abs() >= coords[1] - coords[0])
						break;
					z = applyFunction (c, z);
				}
				
				if (k < MAX_ITERATIONS)
					image.setRGB(i, j, Color.HSBtoRGB((k + 100) / 256.0f , 1, k / (k + 6.0f)));
				else 
					image.setRGB(i, j, new Color(0, 0, 0).getRGB());
			}
		}
		if(quiet != false)
			System.out.println("Thread-<" + indexOfThread + "> stoped. Execution time was (millis): " + (System.currentTimeMillis() - startTimer));
	}

}
