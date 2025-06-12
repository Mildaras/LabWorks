import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;
import java.util.ArrayList;
import java.util.List;

public class DrawingGraphics extends JPanel {
    private final int width;
    private final int height;
    
    List<List<Place>> travelers;
    
    public DrawingGraphics(int w, int h, List<List<Place>> t){
        width = w;
        height = h;
        travelers = t;
    }
    
    private Ellipse2D.Double createPoint(Place place){
        double x = (place.X - 308899.316497516 + 2) / 1000 * width / 450;
        double y = (place.Y - 5986842.71600167 + 2) / 1000 * height / 450;
        return new Ellipse2D.Double(x - 2, y - 2, 5, 5);
    }
    
    private Line2D.Double createLine(double x1, double y1, double x2, double y2){
        double scaledX1 = (x1 - 308899.316497516 + 2) / 1000 * width / 450;
        double scaledY1 = (y1 - 5986842.71600167 + 2) / 1000 * height / 450;
        double scaledX2 = (x2 - 308899.316497516 + 2) / 1000 * width / 450;
        double scaledY2 = (y2 - 5986842.71600167 + 2) / 1000 * height / 450;
        return new Line2D.Double(scaledX1, scaledY1, scaledX2, scaledY2);
    }
    
    @Override
    protected void paintComponent(Graphics g){
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;
        
        RenderingHints rh = new RenderingHints(
            RenderingHints.KEY_ANTIALIASING,
            RenderingHints.VALUE_ANTIALIAS_ON);
        g2d.setRenderingHints(rh);
        
        g2d.setBackground(Color.BLACK);
        g2d.clearRect(0, 0, getWidth(), getHeight());

        List<Color> colors = new ArrayList<>();
        colors.add(new Color(255, 255, 0, 100));
        colors.add(new Color(0, 255, 255, 100));
        colors.add(new Color(255, 0, 0, 100));
    
        for (int i = 0; i < travelers.size(); i++)
        {
            List<Place> path = travelers.get(i);
            
            //Drawing all points
            for(Place place : path)
            {
                g2d.setColor(colors.get(i));
                g2d.fill(createPoint(place));
            }
    
            //Drawing first point in different color
            g2d.setColor(colors.get(i).brighter());
            g2d.fill(createPoint(path.get(0)));
    
            //Drawing all lines
            for (int j = 0; j < path.size() - 1; j++) {
                double x1 = path.get(j).X;
                double y1 = path.get(j).Y;
        
                double x2 = path.get(j + 1).X;
                double y2 = path.get(j + 1).Y;
                g2d.setColor(colors.get(i));
                g2d.draw(createLine(x1, y1, x2, y2));
            }
        }
    }
}
