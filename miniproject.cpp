#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;

void B_Sort(int a[], int s) {
    for (int i = 0; i < s - 1; i++) {
        for (int j = 0; j < s - 2 - i; j++) {
            if (a[j] < a[j + 1]) {
                int T = a[j];
                a[j] = a[j + 1];
                a[j + 1] = T;
            }
        }
    }
}

struct PGMImage {
    int H, W, MaxGray;
    string Comment;
    string MagicNo;
    vector<vector<int>> ImageData;

    PGMImage() {
        cout << "HERE" << endl;
        H = W = MaxGray = -1;
    }

    void Create(vector<vector<int>>& Img, int H, int W) {
        Img = vector<vector<int>>(H);
        for (int i = 0; i < H; i++)
            Img[i] = vector<int>(W);
        return;
    }

    bool ReserveMemory() {
        // Code to create memory storage for the image
        // This code assumes that H and W have been set earlier
        cout << W << " " << H << endl;
        if (H < 0 || W < 0)
            return false;
        Create(ImageData, H, W);
        return true;
    }

    bool LoadImage(char FileName[]) {
        // Code to open File, Reserve Memory and load image data in memory
        ifstream FIN(FileName);

        if (!FIN.is_open())
            return false;

        getline(FIN, MagicNo);
        getline(FIN, Comment); // reading the comment. PROBLEM HERE THE COMMENTIS OPTIONAL
        FIN >> W >> H >> MaxGray;
        if (!ReserveMemory())
            return false;

        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                FIN >> ImageData[r][c];
            }
        }

        FIN.close();
        return true;
    }

    bool SaveImage(char FileName[]) {
        // Code to open File, Reserve Memory and load image data in memory
        if (H < 0)
            return false;

        ofstream FOUT(FileName);
        // Your Code to check if the file has been created for output
        // If File not created then return false

        FOUT << "P2" << endl
            << "# Created By MB For BDS-1A and BDS-1C" << endl
            << W << " " << H << endl
            << MaxGray << endl;

        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                FOUT << ImageData[r][c] << " ";
            }
            FOUT << endl;
        }
        FOUT.close();
        return true;
    }

    bool Create_Negative() {
        // Your Code for computing negative image
        // goes here. Each picel of the 
        // negative is computed by subtracting
        // each pixel from the maximum gray scale value
        if (H < 0)
            return false;
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++)
                ImageData[r][c] = MaxGray - ImageData[r][c];
        }
        return true;
    }

    bool Mean_Filter(int FilterSize = 3) {
        // create a new image in memory
        // apply mean filter and then copy the result
        // back to the same image

        // For mean filtering see online help at
        //https://en.wikipedia.org/wiki/Median_filter
        if (H < 0)
            return false;
        vector<vector<int>>Temp;
        Create(Temp, H, W);
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                int k = 0;
                int sum = 0;
                for (int i = abs(r - FilterSize / 2); i < r + FilterSize / 2; i++) {
                    for (int j = abs(c - FilterSize / 2); j < c + FilterSize / 2; j++)
                    {
                        if (i >= 0 && i < H && i >= 0 && i < W) {
                            sum += ImageData[i][j];
                            k++;

                        }
                    }
                }
                if (k != 0)
                    Temp[r][c] = sum / k;
            }

        }
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                ImageData[r][c] = Temp[r][c];
            }
        }
    }

    bool Median_Filter(int FilterSize = 3) {
        // create a new image in memory
        // apply median filter and then copy the result
        // back to the same image

        // For mean filtering see online help at
        //https://en.wikipedia.org/wiki/Median_filter 
        if(H < 0)
        return false;
        vector<vector<int>> Temp;
        Create(Temp, H, W);
        int D[100];
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                int k = 0;
                for (int i = r - FilterSize / 2; i < r + FilterSize / 2; i++) {
                    for (int j = c - FilterSize / 2; j < c + FilterSize / 2; j++) {
                        if (i >= 0 && i < H && j >= 0 && j < W) {
                            D[k] = ImageData[i][j];
                            k++;
                        }
                    }
                }
                B_Sort(D, k);
                Temp[r][c] = D[k / 2];
            }
        }
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                ImageData[r][c] = Temp[r][c];
            }
        }
        return true;
    }

};

bool Rotate(double angle, int aboutx = 0, int abouty = 0) {
    int m, k, r, c,Maximum,H,W;
    angle = (3.14 * angle) / 180.0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            m = ((i - aboutx) * cos(angle) + (j - abouty) * sin(angle)) + aboutx;
            k = ((j - abouty) * cos(angle) - (i - aboutx) * sin(angle)) + abouty;
           
        }
    }
    H = r;
   W = c;
    Maximum = Maximum;

    return true;
}
bool RotateClockwise() {
    int r, c, image,i;
    for (int i = 0; i < image.size(); i++) {
        for (int j = i; j < image[i].size(); j++) {
            if (i != j) {
                int temp = Img[i][j];
                image[i][j] = image[j][i];
                image[j][i] = temp;
            }
        }
    }

    //no.of rows=r
    //no.of columns=c
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c / 2; j++) {
            int temp = image[i][j];
            image[i][j] = image[i][c - j - 1]
                image[i][c - j - 1] = temp;
        }
    }
    return true;
}
bool RotateCounterClockwise() {

    return true;
}
bool FlipHorizontal() {
        /*
        Function for performing horizontal flip;
        */
    
        int temp[maxrows][maxcols];
        for (int i = Rows - 1, d = 0; i >= 0 && d < Rows; i--, d++)
        {
            for (int j = 0; j < c; j++)
            {
                temp[d][j] = Image[i][j];
            }
        }
        for (int d = 0; d < Rows; d++)
        {
            for (int j = 0; j < Cols; j++)
            {
                Image[d][j] = temp[d][j];
            }
        }
    
    return true;
}
bool FlipVerttical() {
    /*
    Function for performing Vertical flip;
    */
    int temp[MaxRows][MaxCols];
    for (int i = 0; i < Rows; i++)
    {
        for (int j = 0, d = Cols; j < Cols; d--, j++)
        {
            temp[i][j] = Image[i][d];
        }
    }
    for (int i = 0; i < Rows; i++)
    {
        for (int j = 0; j < Cols; j++)
        {
            Image[i][j] = temp[i][j];
        }
    }
    return true;
}
bool Resize((int NewH, int NewW) {
    /*
        Change the rows and columns by the ratio
    */
    double R = Rows / Ratio, C = Cols / Ratio;
    Resize(Result, R, C);
    return true;
}

bool CropImage(int Left, int Top, int Right, int Bottom) {
    for (int i = top, a = 0; i < bottom; i++, a++)
    {
        for (int j = left, b = 0; j < right; j++, b++)
        {
            Image[a][b] = Image[i][j];
        }
    }
    Rows = bottom - top;
    Cols = right - left;



    return true;
}
bool ApplyTransformation(double TrasformationMatrix[][3]) {
    int Mask;
    double I, J, Z;
    for (int i = 1; i < Rows; i++)
    {
        for (int j = 1; j < Cols; j++)
        {
            Two.Image[((Mask[0][0] * i) + (Mask[0][1] * j) + (Mask[0][2])) / ((Mask[2][0] * i) + (Mask[2][1] * j) + (Mask[2][2]))]
                [((Mask[1][0] * i) + (Mask[1][1] * j) + (Mask[1][2])) / ((Mask[2][0] * i) + (Mask[2][1] * j) + (Mask[2][2]))] = Image[i][j];
        }

    }
}
    return true;

};


int Menu()
{
    int choice;
    do {
        cout << endl << "1. Load Image" << endl
            << "2. Save Image" << endl
            << "3. Create Negative Image" << endl
            << "4. Mean Filter" << endl
            << "5. Median Filter" << endl
            << "6. Exit" << endl << endl
            << "Enter Your Choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 6)
            return choice;

    } while (choice < 1 || choice > 6);

}

int main()
{
    PGMImage Image;

    int Choice;
    char FileName[100];

    do {
        Choice = Menu();
        if (Choice == 1) {
            cout << "Enter File Name ";
            cin >> FileName;
            if (Image.LoadImage(FileName))
                cout << "Image Loaded Successfully " << endl;
            else
                cout << "Image Not Loaded Successfully " << endl;
        }
        else if (Choice == 2) {
            cout << "Enter File Name ";
            cin >> FileName;
            if (Image.SaveImage(FileName))
                cout << "Image Saved Successfully " << endl;
            else
                cout << "Image Not Saved Successfully " << endl;

        }
        else if (Choice == 3) {
            if (Image.H < 0)
                cout << "No Image Loaded" << endl;
            else
                Image.Create_Negative();
        }
        else if (Choice == 5) {
            int S;
            cout << "Filter Size ";
            cin >> S;
            Image.Median_Filter(S);
        }
        else if (Choice == 6) {

        }
        else if (Choice == 7) {

        }
        else if (Choice == 8) {

        }
        else if (Choice == 9) {

        }
        else if (Choice == 10) {

        }
        else if (Choice == 11) {

        }
        else if (Choice == 12) {

        }
        else if (Choice == 13) {

        }

    } while (Choice != 14);

    return 0;
}
