using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Threading;


namespace LD1
{
    class Program
    {
        public class Point
        {
            public double x;
            public double y;

            public Point(double x, double y)
            {
                this.x = x;
                this.y = y;
            }
        }
        public class Line
        {
            public double xStart;
            public double xEnd;
            public double yStart;
            public double yEnd;
            public string orientation;

            public Line(double xStart, double yStart, double xEnd, double yEnd, string orientation)
            {
                this.xStart = xStart;
                this.yStart = yStart;
                this.xEnd = xEnd;
                this.yEnd = yEnd;
                this.orientation = orientation;
            }
            public Point PointA()
            {
                return new Point(this.xStart, this.yStart);
            }
            public Point PointB()
            {
                return new Point(this.xStart + (this.xEnd - this.xStart) / 3,
                    this.yStart + (this.yEnd - this.yStart) / 3);
            }
            public Point PointC()
            {
                Point tempA = PointB();
                Point tempB = PointD();
                double tempX = tempB.x - tempA.x;
                double tempY = tempB.y - tempA.y;
                Point temp = new Point(tempX, tempY);
                double angleInRadians;
                if (orientation == "top") angleInRadians = -60 * (Math.PI / 180);
                else angleInRadians = 60 * (Math.PI / 180);
                double x = temp.x * Math.Cos(angleInRadians) + temp.y * Math.Sin(angleInRadians);
                double y = -1 * temp.x * Math.Sin(angleInRadians) + temp.y
                    * Math.Cos(angleInRadians);
                x += tempA.x;
                y += tempA.y;
                Point c = new Point(x, y);
                return c;
            }

            public Point PointD()
            {
                return new Point(this.xStart + ((this.xEnd - this.xStart)) / 3 * 2,
                    this.yStart + ((this.yEnd - this.yStart) / 3) * 2);
            }

            public Point PointE()
            {
                return new Point(this.xEnd, this.yEnd);
            }
            internal class Renderer
            {
                // Color format is ARGB (to define recomended hex: 0xAARRGGBB),
                // coordinates start from bottom left corner, 1 unit is 1 pixel
                public Renderer(string outputName, ushort Width, ushort Height, uint FillingColor)

                {
                    this.Width = Width;
                    this.Height = Height;
                    Buffer = new uint[Width * Height];

                    Array.Fill(Buffer, FillingColor);

                    this.outputName = outputName;
                    if (!outputName.Contains(".bmp"))
                        this.outputName += ".bmp";
                }

                public void Draw(double X0, double Y0, double X1, double Y1, int[] array, double Precision = 1, uint Color = 0)
                {
                    double Length = Math.Sqrt(Math.Pow(X0 - X1, 2) + Math.Pow(Y0 - Y1, 2));
                    double XStep = (X1 - X0) / (Length / Precision);
                    double YStep = (Y1 - Y0) / (Length / Precision);
                    double XRun = X0;
                    double YRun = Y0;
                    for (double i = 0; i < Length; i += Precision)
                    {
                        array[0]++;
                        XRun += XStep;
                        YRun += YStep;
                        SetPixel(XRun, YRun, Color);
                    }
                }

                public void Erase(double X0, double Y0, double X1, double Y1, int[] array, double Precision = 0.5,
                    uint Color = 0xffffff)
                {
                    double Length = Math.Sqrt(Math.Pow(X0 - X1, 2) + Math.Pow(Y0 - Y1, 2));

                    double XStep = (X1 - X0) / (Length / Precision);
                    double YStep = (Y1 - Y0) / (Length / Precision);

                    double XRun = X0;
                    double YRun = Y0;
                    for (double i = 0; i < Length; i += Precision)
                    {
                        array[0]++;
                        XRun += XStep;
                        YRun += YStep;

                        SetPixel(XRun, YRun, Color);
                    }
                }
                private void SetPixel(double X, double Y, uint Color)
                {
                    int Pixel = GetPixel(X, Y);
                    if (Pixel < 0)
                        return;

                    Buffer[Pixel] = Color;
                }

                private int GetPixel(double X, double Y)
                {
                    int Pixel = ((int)Math.Round(Y) * Width) + (int)Math.Round(X);
                    if (Pixel > Buffer.Length)
                        return -1;

                    if (X < 0)
                        return -1;
                    else if (X > Width)
                        return -1;

                    return Pixel;
                }
                public void DrawFirstShape(Renderer render, double X, double Y, double Size, ArrayList list, int[] array)
                {
                    double line = Size / 3;
                    //Virsus
                    render.Draw(X + line * 1.5, Y + line * 1.5, X + line * 0.5, Y + line * 1.5, array);
                    render.Draw(X + line * 0.5, Y + line * 1.5, X + line * 0, Y + line * 0.5, array);
                    //render.Draw(X + line * 0, Y + line * 0.5, X + line * -0.5, Y + line * 1.5, array);
                    render.Draw(X + line * -0.5, Y + line * 1.5, X + line * -1.5, Y + line * 1.5, array);
                    list.Add(new Line(X + line * 1.5, Y + line * 1.5, X + line * 0.5, Y + line * 1.5, "top"));
                    list.Add(new Line(X + line * 0.5, Y + line * 1.5, X + line * 0, Y + line * 0.5, "top"));
                    list.Add(new Line(X + line * 0, Y + line * 0.5, X + line * -0.5, Y + line * 1.5, "top"));
                    list.Add(new Line(X + line * -0.5, Y + line * 1.5, X + line * -1.5, Y + line * 1.5, "top"));

                    //Desine
                    render.Draw(X + line * 1.5, Y + line * 1.5, X + line * 1.5, Y + line * 0.5, array);
                    render.Draw(X + line * 1.5, Y + line * 0.5, X + line * 0.5, Y + line * 0, array);
                    render.Draw(X + line * 0.5, Y + line * 0, X + line * 1.5, Y + line * -0.5, array);
                    render.Draw(X + line * 1.5, Y + line * -0.5, X + line * 1.5, Y + line * -1.5, array);
                    list.Add(new Line(X + line * 1.5, Y + line * 1.5, X + line * 1.5, Y + line * 0.5, "left"));
                    list.Add(new Line(X + line * 1.5, Y + line * 0.5, X + line * 0.5, Y + line * 0, "left"));
                    list.Add(new Line(X + line * 0.5, Y + line * 0, X + line * 1.5, Y + line * -0.5, "left"));
                    list.Add(new Line(X + line * 1.5, Y + line * -0.5, X + line * 1.5, Y + line * -1.5, "left"));
                    //Kaire
                    render.Draw(X + line * -1.5, Y + line * -1.5, X + line * -1.5, Y + line * -0.5, array);
                    render.Draw(X + line * -1.5, Y + line * -0.5, X + line * -0.5, Y + line * 0, array);
                    render.Draw(X + line * -0.5, Y + line * 0, X + line * -1.5, Y + line * 0.5, array);
                    render.Draw(X + line * -1.5, Y + line * 0.5, X + line * -1.5, Y + line * 1.5, array);
                    list.Add(new Line(X + line * -1.5, Y + line * -1.5, X + line * -1.5, Y + line * -0.5, "left"));
                    list.Add(new Line(X + line * -1.5, Y + line * -0.5, X + line * -0.5, Y + line * 0, "left"));
                    list.Add(new Line(X + line * -0.5, Y + line * 0, X + line * -1.5, Y + line * 0.5, "left"));
                    list.Add(new Line(X + line * -1.5, Y + line * 0.5, X + line * -1.5, Y + line * 1.5, "left"));
                    //Apacia
                    render.Draw(X + line * -1.5, Y + line * -1.5, X + line * -0.5, Y + line * -1.5, array);
                    render.Draw(X + line * -0.5, Y + line * -1.5, X + line * 0, Y + line * -0.5, array);
                    render.Draw(X + line * 0, Y + line * -0.5, X + line * 0.5, Y + line * -1.5, array);
                    render.Draw(X + line * 0.5, Y + line * -1.5, X + line * 1.5, Y + line * -1.5, array);
                    list.Add(new Line(X + line * -1.5, Y + line * -1.5, X + line * -0.5, Y + line * -1.5, "top"));
                    list.Add(new Line(X + line * -0.5, Y + line * -1.5, X + line * 0, Y + line * -0.5, "top"));
                    list.Add(new Line(X + line * 0, Y + line * -0.5, X + line * 0.5, Y + line * -1.5, "top"));
                    list.Add(new Line(X + line * 0.5, Y + line * -1.5, X + line * 1.5, Y + line * -1.5, "top"));
                }

                public void DrawRecursiveShape(Renderer Render, ArrayList lines, int[] array, int i)
                {
                    if (i == 0) return;
                    ArrayList newList = new ArrayList();
                    foreach (Line line in lines)
                    {
                        Point a = line.PointA();
                        Point b = line.PointB();
                        Point c = line.PointC();
                        Point d = line.PointD();
                        Point e = line.PointE();

                        //Render.Draw(a.x, a.y, b.x, b.y, array);
                        //Render.Draw(b.x, b.y, c.x, c.y, array);
                        //Render.Draw(c.x, c.y, d.x, d.y, array);
                        //Render.Draw(d.x, d.y, e.x, e.y, array);
                        //Render.Erase(b.x, b.y, d.x, d.y, array);
                        newList.Add(new Line(a.x, a.y, b.x, b.y, line.orientation));
                        newList.Add(new Line(b.x, b.y, c.x, c.y, line.orientation));
                        newList.Add(new Line(c.x, c.y, d.x, d.y, line.orientation));
                        newList.Add(new Line(d.x, d.y, e.x, e.y, line.orientation));
                    }
                    i--;
                    DrawRecursiveShape(Render, newList, array, i);
                }

                public void Write()
                {
                    using (FileStream File = new FileStream(outputName, FileMode.Create, FileAccess.Write))
                    {
                        File.Write(new byte[] { 0x42, 0x4D }); // BM
                        File.Write(BitConverter.GetBytes(Height * Width * sizeof(uint) + 0x1A)); // Size
                        File.Write(BitConverter.GetBytes(0)); // Reserved (0s)
                        File.Write(BitConverter.GetBytes(0x1A)); // Image Offset (size of the header)
                        File.Write(BitConverter.GetBytes(0x0C)); // Header size (size is 12 bytes)
                        File.Write(BitConverter.GetBytes(Width)); // Width
                        File.Write(BitConverter.GetBytes(Height)); // Height
                        File.Write(BitConverter.GetBytes((ushort)1)); // Color plane
                        File.Write(BitConverter.GetBytes((ushort)32)); // bits per pixel
                        byte[] Converted = new byte[Buffer.Length * sizeof(uint)];
                        System.Buffer.BlockCopy(Buffer, 0, Converted, 0, Converted.Length);
                        File.Write(Converted);
                        File.Close();
                    }
                }

                private readonly uint[] Buffer;
                private readonly ushort Width;
                private readonly ushort Height;
                private readonly string outputName;

            }

            //T(n)=3∗T(n/6)+n^2
            static void First(int[] array, int n, int m)
            {

                if (m - n < 3)
                {
                    return;
                }

                First(array, n, n + (m - n) / 6);
                First(array, m - (m - n) / 6, m);
                First(array, m - (n - m) / 6, m);

                for (int i = n; i < m; i++)
                {
                    for (int j = n; j < m; j++)
                    {
                        array[0]++;
                    }
                }
            }

            //T(n)=T(n/10)+ T(n/3)+ n
            static void Second(int[] array, int n, int m)
            {
                if (m - n < 9)
                {
                    return;
                }

                Second(array, n, n + (m - n) / 3);
                Second(array, m - (m - n) / 10, m);

                for (int i = 0; i < n; i++)
                {
                    array[0]++;
                }
            }

            //T(n)=T(n−9)+ T(n−1)+1
            static void Third(int[] array, int n)
            {

                if (n <= 10)
                {
                    return;
                }

                Third(array, n - 9);
                Third(array, n - 1);
                
                array[0]++;
            }

            static void Main(string[] args)
            {
                ushort pixels = 200;
                int iterations = 3;
                for (int i = 0; i < 5; i++)
                {
                    ArrayList newList = new ArrayList();
                    pixels *= 2;
                    int[] array = new int[10];
                    var render = new Renderer("Result" + i, pixels, pixels, 0xffffff);

                    var watch = System.Diagnostics.Stopwatch.StartNew();
                    render.DrawFirstShape(render, pixels / 2.0, pixels / 2.0, pixels / 5.0 * 3.0, newList, array);
                    render.DrawRecursiveShape(render, newList, array, iterations);
                    render.Write();
                    watch.Stop();

                    var elapsedMs = watch.ElapsedMilliseconds;
                    Console.WriteLine(pixels + "X" + pixels + " dydis, " + array[0] + " veiksmų skaičius = " + elapsedMs + " ms");
                }


                int m = 50;
                
                Console.WriteLine("Pirma");
                for (int i = 0; i < 5; i++)
                {
                    int[] array = new int[m];
                    var watch = System.Diagnostics.Stopwatch.StartNew();
                    //m = 1000000; m *= 2;
                    First(array, 0, array.Length);

                    //m = 100; m*=2
                    //Second(array, 0, array.Length);

                    //m = 70; m += 10;
                    //Third(array, array.Length);

                    watch.Stop();
                    var elapsedMs = watch.ElapsedMilliseconds;
                    Console.WriteLine(m + " iteraciju skaicius, " + array[0] + " veiksmų skaicius = " + elapsedMs + " ms");
                    m *= 5;
                }

                m = 20000;
                Console.WriteLine("Antra");
                for (int i = 0; i < 5; i++)
                {
                    int[] array = new int[m];
                    var watch = System.Diagnostics.Stopwatch.StartNew();
                    //m = 1000000; m *= 2;
                    //First(array, 0, array.Length);

                    //m = 100; m*=2
                    Second(array, 0, array.Length);

                    //m = 70; m += 10;
                    //Third(array, array.Length);

                    watch.Stop();
                    var elapsedMs = watch.ElapsedMilliseconds;
                    Console.WriteLine(m + " iteraciju skaicius, " + array[0] + " veiksmų skaicius = " + elapsedMs + " ms");
                    m += 500000;
                }

                m = 70;
                Console.WriteLine("Trecia");
                for (int i = 0; i < 5; i++)
                {
                    int[] array = new int[m];
                    var watch = System.Diagnostics.Stopwatch.StartNew();
                    //m = 1000000; m *= 2;
                    //First(array, 0, array.Length);

                    //m = 100; m*=2
                    //Second(array, 0, array.Length);

                    //m = 70; m += 10;
                    Third(array, array.Length);

                    watch.Stop();
                    var elapsedMs = watch.ElapsedMilliseconds;
                    Console.WriteLine(m + " iteraciju skaicius, " + array[0] + " veiksmų skaicius = " + elapsedMs + " ms");
                    m += 10;
                }
            }
        }

    }
}

