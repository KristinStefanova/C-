import java.io.IOException;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.DefaultParser;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;

public class Main {
	
	public static Options createOptions() {
        Option size = new Option("s", "size", true, "size of the image");
        Option rect = new Option("r", "rect", true, "coordinate plane");
        Option tasks = new  Option("t", "tasks", true, "number of tasks");
        Option output = new  Option("o", "output", true, "output file");
        Option quiet = new Option("q", "quiet", false, "quite mode");

        Options options = new Options();
        options.addOption(size);
        options.addOption(rect);
        options.addOption(tasks);
        options.addOption(output);
        options.addOption(quiet);
        
        return options;
    }

    private static CommandLine createCmd(Options options, String[] args) {
        CommandLineParser parser = new DefaultParser();
        try {
            return parser.parse(options, args);
        } catch(ParseException ex) {
            throw new IllegalArgumentException("Parsing error: " + ex.getMessage());
        }
    }

    private static MandelbrotCompute createMandelbrot(CommandLine cmd) {
        int width = 640, height = 480;
        if(cmd.hasOption("s")) {
            String arg = cmd.getOptionValue("s");
            String[] res = arg.split("x");
            width = Integer.parseInt(res[0]);
            height = Integer.parseInt(res[1]);

            if(width < 0 || height < 0) {
                throw new IllegalArgumentException("width and height must be > 0");
            }
        }

        double[] limits = new double[4];
        limits[0] = -2.0; limits[1] = 2.0; // x
        limits[2] = -2.0; limits[3] = 2.0; // y
       
        if(cmd.hasOption("r")) {
            String arg = cmd.getOptionValue("r");
            String[] res = arg.split(":");
            limits[0] = Double.parseDouble(res[0]);
            limits[1] = Double.parseDouble(res[1]);
            limits[2] = Double.parseDouble(res[2]);
            limits[3] = Double.parseDouble(res[3]);
        }

        int threadCount = 1;
        if(cmd.hasOption("t")) {
            threadCount = Integer.parseInt(cmd.getOptionValue("t"));

            if(threadCount < 1) {
                throw new IllegalArgumentException("tasks must be > 0");
            }
        }
        
        String output = "zad16.png";
        if(cmd.hasOption("o")) {
        	output = cmd.getOptionValue("o");
        }

        boolean inQuietMode = false;
        if(cmd.hasOption("q")) {
            inQuietMode = true;
        }

        return new MandelbrotCompute(width, height,threadCount, output, limits, inQuietMode);
    }

    public static void generate(String[] args) throws IOException {
        Options options = createOptions();
        CommandLine cmd = createCmd(options, args);
        MandelbrotCompute mandelbrot = createMandelbrot(cmd);

        mandelbrot.Mendelbrot();
    }

    public static void main(String[] args) throws IOException {
    	generate(args);
    }
}