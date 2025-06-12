import java.io.File;
import java.io.FileInputStream;
import java.util.*;

import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import javax.swing.*;

public class Optimal {
    
    public static void main(String[] args) {
        String data = "./IP_data_2023.xlsx";
        int numberOfPlaces = 12;
        long start, end;

        List<Place> places = ReadFromXLSX(data); 
        
        //Collections.shuffle(places, new Random(1));
        
        List<Place> placesSubList = places.subList(0, numberOfPlaces);
        
        List<Place> startingPlaces = new ArrayList<>();
        startingPlaces.add(placesSubList.get(0));
        startingPlaces.add(placesSubList.get(1));

        
        List<List<Place>> travelersPaths = new ArrayList<>();
        start = System.currentTimeMillis();
        travelersPaths = optimalMTSP(startingPlaces, placesSubList);
        end = System.currentTimeMillis();
    
        for (var path : travelersPaths) {
            System.out.println(getPathPrice(path));
        }
        
        for (int i = 0; i < travelersPaths.size(); i++) {
            System.out.printf(" _______________________________ \n");
            System.out.printf("|        %d Keliautojas         |\n", i + 1);
            System.out.printf("|_______________________________|\n");
            System.out.printf("|       Vietos pavadinimas      |\n");
            System.out.printf("|_______________________________|\n");
            for (var place : travelersPaths.get(i)) {
                System.out.println(place.Name);
            }
            System.out.print("Total price: ");
            System.out.print("\u001B[32m" + getPathPrice(travelersPaths.get(i)) + "\u001B[0m\n");
        }

        System.out.printf("Vietoviu kiekis: %-20d Laiko uztrukta, s: %-20f\n", numberOfPlaces, (double) (end - start) / 1000);
    
        DisplayGraphics(travelersPaths);
    }
    
    public static List<List<Place>> optimalMTSP(List<Place> startingPlaces, List<Place> places) {
        List<List<Place>> travelingPaths = new ArrayList<>();
        for (var startingPlace : startingPlaces) {
            List<Place> travelingPath = new ArrayList<>();
            travelingPath.add(startingPlace);
            travelingPaths.add(travelingPath);
            places.remove(startingPlace);
        }
        
        List<int[]> permutations_places = new ArrayList<>();
        int[] permutation = new int[places.size()];
        Arrays.fill(permutation, -1);
        Permutations(places.size(), 0, permutation, permutations_places);
        
        List<int[]> combinations_travelers = new ArrayList<>();
        Combinations(startingPlaces.size(), 0, new int[places.size()], combinations_travelers);
    
        List<List<Place>> cheapestTravelingPaths = new ArrayList<>();
        double minPrice = Double.MAX_VALUE;
        for (var travelCombination : combinations_travelers) {
            for (var placesPermutation : permutations_places) {
                List<List<Place>> newTravelingPaths = new ArrayList<>();
                for (List<Place> travelingPath : travelingPaths) {
                    List<Place> travelersPath = new ArrayList<>();
                    travelersPath.add(travelingPath.get(0));
                    newTravelingPaths.add(travelersPath);
                }
                
                for (int i = 0; i < places.size(); i++)
                    newTravelingPaths.get(travelCombination[i]).add(places.get(placesPermutation[i]));
    
                for (var travelersPath : newTravelingPaths)
                    travelersPath.add(travelersPath.get(0));
                
                double currentPrice = 0;
                for (List<Place> travelingPath : newTravelingPaths)
                    currentPrice += getPathPrice(travelingPath);
                
                if (currentPrice < minPrice) {
                    minPrice = currentPrice;
                    cheapestTravelingPaths = new ArrayList<>(newTravelingPaths);
                }
            }
        }
        
        return cheapestTravelingPaths;
    }
    
    
    
    public static void Combinations(int n, int currentIndex, int[] combination, List<int[]> combinations) {
        if (currentIndex < n) {
            for (int i = 0; i < n; i++) {
                combination[currentIndex] = i;
                Combinations(n, currentIndex + 1,  combination, combinations);
            }
        } else {
            combinations.add(Arrays.copyOf(combination, combination.length));
        }
    }
    
    public static void Permutations(int n, int currentIndex, int[] permutation, List<int[]> permutations) {
        if (currentIndex < n) {
            for (int i = 0; i < n; i++) {
                if (!contains(permutation, i)) {
                    permutation[currentIndex] = i;
                    Permutations(n, currentIndex + 1,  permutation, permutations);
                    permutation[currentIndex] = -1;
                }
            }
        } else {
            permutations.add(Arrays.copyOf(permutation, permutation.length));
        }
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
    
    public static List<Place> ReadFromXLSX(String filePath) {
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
            }
            workbook.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return places;
    }
}
