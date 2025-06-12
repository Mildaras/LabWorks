public class Place{
    public String Name;
    public double Id;
    public double X;
    public double Y;
    
    public Place(String name, double id, double x, double y){
        Name = name;
        Id = id;
        X = x;
        Y = y;
    }
    
    @Override
    public String toString() {
        return String.format("%-60s %10.0f %f %f", Name, Id, X, Y);
    }
}