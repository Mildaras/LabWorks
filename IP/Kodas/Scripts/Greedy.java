import java.io.File;
import java.io.FileInputStream;
import java.util.*;

import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import javax.swing.*;

public class Greedy {
    
    public static void main(String[] args) {
        String data = "./IP_data_2023.xlsx";
        int numberOfPlaces = 314;
        long start, end;

        List<Place> places = ReadFromFile(data);
        
        //Collections.shuffle(places, new Random(98));
        
        List<Place> placesSubList = places.subList(0, numberOfPlaces);
        
        List<Place> startingPlaces = new ArrayList<>();
        startingPlaces.add(placesSubList.get(0));
        startingPlaces.add(placesSubList.get(1));
    
        start = System.currentTimeMillis();
        List<List<Place>> travelersPaths = GreedyMTSP(startingPlaces, placesSubList);
        end = System.currentTimeMillis();

        for (int i = 0; i < travelersPaths.size(); i++) {
            System.out.printf("-------- %d Keliautojas --------\n", i + 1);
            System.out.printf("________________________________\n");
            System.out.printf("         Vietos pavadinimas     \n");
            System.out.printf("________________________________\n");
            for (var place : travelersPaths.get(i)) {
                System.out.println(place.Name);
            }
            System.out.print("Total price: ");
            System.out.print("\u001B[32m" + getPathPrice(travelersPaths.get(i)) + "\u001B[0m\n");
        }
        
        System.out.printf("Vietoviu kiekis: %-20d Laiko uztrukta, s: %-20f\n", numberOfPlaces, (double) (end - start) / 1000);
        DisplayGraphics(travelersPaths);
    }
    
    public static List<List<Place>> GreedyMTSP(List<Place> startingPlaces, List<Place> places) {
        List<List<Place>> travelersPaths = new ArrayList<>();                              
        
        for (var startingPlace : startingPlaces) {                                         //O(k)
            List<Place> travelersPath = new ArrayList<>();                                 
            travelersPath.add(startingPlace);
            travelersPaths.add(travelersPath);
            places.remove(startingPlace);
        }
        
        while (places.size() > 0) {                                                        //O(n)
            for (List<Place> path : travelersPaths) {                                      //O(n^2)
                if (places.size() > 0) {                                                   
                    Place cheapestPlaceMove = getGreedyPlace(path.get(path.size() - 1), places);
                    path.add(cheapestPlaceMove);
                    places.remove(cheapestPlaceMove);
                }
            }
        }
        
        for (var travelersPath : travelersPaths) {
            travelersPath.add(travelersPath.get(0));
        }
        
        return travelersPaths;
    }  
    
    public static double getPathPrice(List<Place> path) {
        double totalPrice = 0;
        for (int i = 0; i < path.size() - 1; i++) {
            totalPrice += getPrice(path.get(i), path.get(i + 1));
        }
        return totalPrice;
    }
    
    private static double getDistance(Place place1, Place place2) {
        return Math.sqrt(Math.pow((place1.X - place2.X), 2) + Math.pow((place1.Y - place2.Y), 2));
    }
    
    private static double getPrice(Place place1, Place place2) {
        return Math.sqrt(getDistance(place1, place2));
    }
    
    public static Place getGreedyPlace(Place startingPlace, List<Place> places) {
        double cheapestMove = Double.MAX_VALUE;
        Place chepeastMovePlace = null;
        for (var place : places) {
            if (place != startingPlace) {
                double currentPrice = getPrice(startingPlace, place);
                if (currentPrice < cheapestMove) {
                    cheapestMove = currentPrice;
                    chepeastMovePlace = place;
                }
            }
        }
        return chepeastMovePlace;
    }

    public static void getMaxMinDiff(List<Place> places) {
        double max_X = 0;
        double max_Y = 0;
        double min_X = Double.MAX_VALUE;
        double min_Y = Double.MAX_VALUE;
        for (var place : places) {
            if (place.X > max_X)
                max_X = place.X;
            if (place.Y > max_Y)
                max_Y = place.Y;
            if (place.X < min_X)
                min_X = place.X;
            if (place.Y < min_Y)
                min_Y = place.Y;
        }
        System.out.println("MAX  X " + max_X + " Y " + max_Y);
        System.out.println("MIN  X " + min_X + " Y " + min_Y);
        System.out.println("DIFF X " + (max_X - min_X) + " Y " + (max_Y - min_Y));
    }
    
    public static void DisplayGraphics(List<List<Place>> travelers) {
        int width = 1920;
        int height = 1080;
        JFrame frame = new JFrame();
        DrawingGraphics dg = new DrawingGraphics(width, height, travelers);
        frame.setSize(width, height);
        frame.setTitle("Places");
        frame.add(dg);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
    
    public static boolean contains(int[] permutation, int value) {
        if (permutation != null) {
            for (int perm : permutation) {
                if (perm == value) {
                    return true;
                }
            }
        }
        return false;
    }
    
    public static List<Place> ReadFromFile(String filePath) {
        List<Place> places = new ArrayList<>();
        
        try {
            File file = new File(filePath);
            FileInputStream fis = new FileInputStream(file);
            XSSFWorkbook workbook = new XSSFWorkbook(fis);
            XSSFSheet sheet = workbook.getSheetAt(0);
            for (Row row : sheet) {
                String name = row.getCell(0).getStringCellValue();
                double id = row.getCell(1).getNumericCellValue();
                double x = row.getCell(2).getNumericCellValue();
                double y = row.getCell(3).getNumericCellValue();
                
                Place place = new Place(name, id, x, y);
                places.add(place);
                workbook.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return places;
    }
}
