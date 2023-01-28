import org.knowm.xchart.*;
import org.knowm.xchart.style.Styler;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;


class Main {
    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(args[0]));//Reading csv file
        String line = br.readLine();
        ArrayList<Integer> data = new ArrayList<>();
        int size=4096;//size of the input data
        int lineNumber=0;
        while (line != null) {
            String[] attributes = line.split(",");
            if(lineNumber>=1 &&lineNumber <=size) {
                data.add(Integer.parseInt(attributes[7]));
            }
            lineNumber++;
            line = br.readLine();
        }

        int[] a=new int[size];//array to be sorted
        for(int i =0;i< data.size();i++){
            a[i]=data.get(i);
        }

        //random data array sort experiment
        long start1 = System.currentTimeMillis();
        countSort(a, a.length);
        long end1 = System.currentTimeMillis();
        System.out.println("Elapsed Time in milliseconds to random data counting sort: "+ (end1-start1));

        //sorted data array sort experiment
        long start2 = System.currentTimeMillis();
        countSort(a, a.length);
        long end2 = System.currentTimeMillis();
        System.out.println("Elapsed Time in milliseconds to sorted data counting sort: "+ (end2-start2));

        //reversing sorted data
        a=reverse(a);

        //reversed data array sort experiment
        long start3 = System.currentTimeMillis();
        countSort(a, a.length);
        long end3 = System.currentTimeMillis();
        System.out.println("Elapsed Time in milliseconds to reversed data counting sort: "+ (end3-start3));


        // X axis data
        int[] inputAxis = {512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 251282};

        // Create sample data for linear runtime
        double[][] yAxis = new double[4][10];
        yAxis[0] = new double[]{0, 8, 8.8, 9.3, 17.3, 42.3, 130.9, 487.9, 2035.5, 8395.4};//insertion sort test results
        yAxis[1] = new double[]{0, 0, 1.6, 4.8, 6.4, 8, 11.2, 20.3, 31.2, 47};//merge sort test results
        yAxis[2] = new double[]{428, 429, 431, 428.4, 437, 438, 437, 438, 453, 469};//pigeonhole sort test results
        yAxis[3] = new double[]{480, 485, 484, 485, 484, 486,500, 515,520, 562};//counting sort test results
        // Save the char as .png and show it
        showAndSaveChart("Random Data Test", inputAxis, yAxis);

        double[][] sortedyAxis = new double[4][10];//sorted data experiment results

        yAxis[0] = new double[]{0, 0.1, 0.2, 0.2, 0.2, 0.3, 0.7, 0.8, 1.8, 3.4};//insertion sort test results
        yAxis[1] = new double[]{0, 0, 0, 0, 1.6, 6.4, 8, 9.4, 12.8, 16};//merge sort test results
        yAxis[2] = new double[]{349, 350, 352, 337.6, 330.6,328, 340, 345, 358, 360};//pigeonhole sort test results
        yAxis[3] = new double[]{266, 266, 265, 266, 265, 281, 281, 282, 300, 310};//counting sort test results

        showAndSaveChart("Sorted Data Test", inputAxis, yAxis);

        double[][] reversedyAxis = new double[4][10];//reversed sorted data experiment results

        yAxis[0] = new double[]{0, 7.5, 7.7, 9.4, 24.8, 65.5, 254, 970.6, 4240, 16260.4};//insertion sort test results
        yAxis[1] = new double[]{0, 0, 1.6, 2.5, 6.4, 8, 9.4, 12.8, 16, 31};//merge sort test results
        yAxis[2] = new double[]{256, 266, 266, 268, 264, 265, 281, 281, 453, 460};//pigeonhole sort test results
        yAxis[3] = new double[]{300, 297, 281, 296, 281, 297, 280, 281, 350, 455};//counting sort test results

        showAndSaveChart("Reversed Data Test", inputAxis, yAxis);


    }

    public static void showAndSaveChart(String title, int[] xAxis, double[][] yAxis) throws IOException {
        // Create Chart
        XYChart chart = new XYChartBuilder().width(800).height(600).title(title)
                .yAxisTitle("Time in Milliseconds").xAxisTitle("Input Size").build();

        // Convert x axis to double[]
        double[] doubleX = Arrays.stream(xAxis).asDoubleStream().toArray();

        // Customize Chart
        chart.getStyler().setLegendPosition(Styler.LegendPosition.InsideNE);
        chart.getStyler().setDefaultSeriesRenderStyle(XYSeries.XYSeriesRenderStyle.Line);

        // Add a plot for a sorting algorithm
        chart.addSeries("Insertion Sort", doubleX, yAxis[0]);
        chart.addSeries("Merge Sort", doubleX, yAxis[1]);
        chart.addSeries("Pigeon Hole", doubleX, yAxis[2]);
        chart.addSeries("Counting Sort", doubleX, yAxis[3]);

        // Save the chart as PNG
        BitmapEncoder.saveBitmap(chart, title + ".png", BitmapEncoder.BitmapFormat.PNG);

        // Show the chart
        new SwingWrapper(chart).displayChart();
    }
    public static void InsertionSort(int[] array){
        for (int i = 1; i < array.length; ++i) {
            int keyItem = array[i];
            int j = i - 1;
            while (j >= 0 && array[j] > keyItem) {
                array[j + 1] = array[j];
                j = j - 1;
            }
            array[j + 1] = keyItem;
        }
    }

    public static void mergeSort(int a[], int beginning, int end) {
        if (beginning < end) {
            int mid = (beginning + end) / 2;
            mergeSort(a, beginning, mid);
            mergeSort(a, mid + 1, end);
            merge(a, beginning, mid, end);
        }
    }

    public static void merge(int a[], int beg, int mid, int end) {
        int i, j, k;
        int n1 = mid - beg + 1;
        int n2 = end - mid;

        int[] LeftArray = new int[n1];
        int[] RightArray = new int[n2];


        for (i = 0; i < n1; i++) {
            LeftArray[i] = a[beg + i];
        }
        for (j = 0; j < n2; j++) {
            RightArray[j] = a[mid + 1 + j];
        }

        i = 0;
        j = 0;
        k = beg;

        while (i < n1 && j < n2) {
            if(LeftArray[i] <= RightArray[j]) {
                a[k] = LeftArray[i];
                i++;
            }
            else {
                a[k] = RightArray[j];
                j++;
            }
            k++;
        }
        while (i<n1) {
            a[k] = LeftArray[i];
            i++;
            k++;
        }

        while (j<n2) {
            a[k] = RightArray[j];
            j++;
            k++;
        }
    }

    public static void pigeonholeSort(int[] array, int n) {

        int min = array[0];
        int max = array[0];
        int range, i, j, index;

        for(int a=0; a<n; a++)
        {
            if(array[a] > max)
                max = array[a];
            if(array[a] < min)
                min = array[a];
        }

        range = max - min + 1;
        int[] pigeonhole = new int[range];
        Arrays.fill(pigeonhole, 0);

        for(i = 0; i<n; i++)
            pigeonhole[array[i] - min]++;
        index = 0;
        for(j = 0; j<range; j++)
            while(pigeonhole[j]-->0)
                array[index++]=j+min;

    }

    public static void countSort(int[] array, int size) {
        int[] output = new int[size + 1];

        int max = array[0];
        for (int i = 1; i < size; i++) {
            if (array[i] > max)
                max = array[i];
        }
        int[] count = new int[max + 1];

        for (int i = 0; i < max; ++i) {
            count[i] = 0;
        }
        for (int i = 0; i < size; i++) {
            count[array[i]]++;
        }

        for (int i = 1; i <= max; i++) {
            count[i] += count[i - 1];
        }
        for (int i = size - 1; i >= 0; i--) {
            output[count[array[i]] - 1] = array[i];
            count[array[i]]--;
        }

        for (int i = 0; i < size; i++) {
            array[i] = output[i];
        }
    }

    public static int[] reverse(int[] a) {
        int[] b = new int[a.length];
        int j = a.length;
        for (int k : a) {
            b[j - 1] = k;
            j = j - 1;
        }
        return b;
    }

}
