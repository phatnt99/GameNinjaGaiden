using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace XuLyAnhChoGame
{
    public partial class Form1 : Form
    {
        List<Image> listImg;
        List<int> listIndex;
        public int c;
        int x;
        int y;
        public Form1()
        {
            InitializeComponent();
            listImg = new List<Image>();
            listIndex = new List<int>();
            x = y = c = 0;
        }
        void CatBackground(string filename)
        {
            //tạo đối tượng ảnh lớn
            AnhLon anhlon = new AnhLon(filename);
            int row = anhlon.anh.Height / 64;
            int col = anhlon.anh.Width / 64;

            //kích thước 64,64
            for (int i=0;i < row;i++)
            {
                for(int j=0;j < col;j++)
                {
                    Image anhnho = anhlon.AnhCat(x + j*64, y + i*64, 64, 64);
                    if (listImg.Count <= 0)
                    {
                        listIndex.Add(c);
                        listImg.Add(anhnho);
                    }
                    else
                    {
                        int co = 0;
                        int temp = 0;
                        for(int k =0; k < listImg.Count;k++)
                        {
                            if (SoSanh(anhnho, listImg[k]))
                            {
                                co = 1;
                                temp = k;
                                break;
                            }
                        }
                        if (co == 0) // ảnh khác nhau
                        {
                            listImg.Add(anhnho);
                            listIndex.Add(++c);
                        }
                        else
                        {
                            listIndex.Add(temp);
                        }
                    }
                }
            }

            // Ghi ma trận
            string[] lines = new string[row];
            int ii = 0;
            int dem = 1;
            for(int i=0; i < listIndex.Count; i++)
            {
                if(dem <= col)
                {
                    lines[ii] += listIndex[i].ToString() + " ";
                    dem++;
                }
                else
                {
                    ii++;
                    lines[ii] += listIndex[i].ToString() + " ";
                    dem = 2;
                }
            }
            File.WriteAllLines("Matrix.txt", lines);

            SaveTitle(listImg);
            MessageBox.Show("Success");
           
        }

        void SaveTitle(List<Image> list)
        {
            int width = 64 * 45;
            int height = 64 * 1;
            Bitmap bitmap = new Bitmap(width, height);
            using (Graphics g = Graphics.FromImage(bitmap))
            {
                int k = 0;
                for (int i = 0; i < 1; i++)
                {
                    for (int j = 0; j < 45; j++)
                    {
                        g.DrawImage(list[k++], 64 * j, i * 64);
                    }
                }
            }

            bitmap.Save("Titles.png", ImageFormat.Png);

            //int width = 64 * 1;
            //int height = 64 * 1;
            //Bitmap bitmap = new Bitmap(width, height);
            //using (Graphics g = Graphics.FromImage(bitmap))
            //{
            //    //int k = 0;
            //    //for (int i = 0; i < 1; i++)
            //    //{
            //    //    for (int j = 0; j < 47; j++)
            //    //    {
            //            g.DrawImage(list[43], 0, 0);
            //    //    }
            //    //}
            //}

            //bitmap.Save("Titles.png", ImageFormat.Png);
        }

        bool SoSanh(Image img1, Image img2)
        {
            string str1, str2;
            Bitmap bmp1 = new Bitmap(img1);
            Bitmap bmp2 = new Bitmap(img2);
            if(bmp1.Width == bmp2.Width && bmp1.Height == bmp2.Height)
            {
                for(int i=0; i < bmp1.Width;i++)
                {
                    for(int j=0;j < bmp1.Height;j++)
                    {
                        str1 = bmp1.GetPixel(i, j).ToString();
                        str2 = bmp2.GetPixel(i, j).ToString();
                        if (str1 != str2)
                            return false;
                    }
                }
                return true;
            }

            else return true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1 = new OpenFileDialog();
            if(openFileDialog1.ShowDialog()==DialogResult.OK)
            {
                string fileName = openFileDialog1.FileName;
                CatBackground(fileName);
            }
        }
    }


    public class AnhLon
    {
        public Image anh;
        public AnhLon(string duongDanAnh)
        {
            anh = Image.FromFile(duongDanAnh);
        }
        public Bitmap AnhCat(int X, int Y, int Width, int Height)
        {
            Bitmap bm = new Bitmap(Width, Height);
            Graphics g = Graphics.FromImage(bm);
            g.DrawImage(anh, -X, -Y);
            return bm;
        }
    }
}
