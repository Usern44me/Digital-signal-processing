#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

int strInInt(const char* str, int size) {
    int res = 0;
    for (int i = 0; i < size; i++) {
        res *= 256;
        res += (int)str[size - 1 - i];
    }
    return res;
}

void setInt(char* str, int size, unsigned int n) {
    for (int i = 0; i < size; i++) {
        str[i] = n % 256;
        n /= 256;
    }
}

double sinc(double x) {
    if (x == 0) {
        return 1;
    }
    return sin(x * M_PI) / x / M_PI;
}

void doSomething(const char* oldName, const char* newName) {
    std::ifstream is(oldName, std::ios::binary);
    if (!(is.is_open())) {
        std::cout << "File " << oldName << " not found." << std::endl;
        return;
    }
    
    double n, m;
    
    std::cout << "Enter n: ";
    std::cin >> n;
    std::cout << "Enter m: ";
    std::cin >> m;

    is.seekg(0, std::ios::end);
    int size = is.tellg();
    is.seekg(0, std::ios::beg);
    char sourse[size];
    is.read(sourse, size);
    is.close();

    std::ofstream os(newName, std::ios::binary);
    int indentation = strInInt(sourse + 10, 4);
    int width = strInInt(sourse + 18, 4);
    int height = strInInt(sourse + 22, 4);
    int pixSize = strInInt(sourse + 28, 2) / 8;
    std::cout << "pixSize = " << pixSize << std::endl
              << "width = " << width << std::endl
              << "height = " << height << std::endl
              << "size = " << size << std::endl << std::endl;
    
    if (width * height * pixSize + indentation != size) {
        std::cout << "ERROR" << std::endl;
        return;
    }
    
    int resWidth = (int)(width * n);
    resWidth -= resWidth % 4;
    n = (double)resWidth / width;
    int resHeight = (int)(height * m);
    int resSize = indentation + resWidth * resHeight * pixSize;
    
    std::cout << "resWidth = " << resWidth << std::endl
              << "resHeight = " << resHeight << std::endl
              << "resSize = " << resSize << std::endl;
    
    char res[resSize];
    for (int i = 0; i < indentation; ++i) {
        res[i] = sourse[i];
    }
    
    setInt(res + 18, 4, resWidth);
    setInt(res + 22, 4, resHeight);
    
    unsigned char*** pix = new unsigned char**[height];
    for (int i = 0; i < height; ++i) {
        pix[i] = new unsigned char*[width];
        for (int j = 0; j < width; ++j) {
            pix[i][j] = new unsigned char[pixSize];
        }
    }
    
    unsigned char*** interPix = new unsigned char**[height];
    for (int i = 0; i < height; ++i) {
        interPix[i] = new unsigned char*[resWidth];
        for (int j = 0; j < resWidth; ++j) {
            interPix[i][j] = new unsigned char[pixSize];
        }
    }
    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int p = 0; p < pixSize; ++p) {
                pix[i][j][p] = strInInt(sourse + indentation + (width * i + j) * pixSize + p, 1);
            }
        }
    }
    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < resWidth; ++j) {
            for (int p = 0; p < pixSize; ++p) {
                double sum = 0;
                for (int c = 0; c < width; ++c) {
                    sum += pix[i][c][p] * sinc(j / n - c);
                }
                if(sum < 0) {
                    sum = 0;
                }
                interPix[i][j][p] = sum;
            }
        }
    }
    
    for (int i = 0; i < resHeight; ++i) {
        for (int j = 0; j < resWidth; ++j) {
            for (int p = 0; p < pixSize; ++p) {
                double sum = 0;
                for (int c = 0; c < height; ++c) {
                    sum += interPix[c][j][p] * sinc(i / m - c);
                }
                if(sum < 0) {
                    sum = 0;
                }
                setInt(res + indentation + (resWidth * i + j) * pixSize + p, 1, sum);
            }
        }
    }

    os.write(res, resSize);
    os.close();
}

int main() {
    char fileName[1000] = {0};
    std::cout << "Enter the name of the source file: ";
    std::cin >> fileName;
    doSomething(fileName, "out.bmp");
    return 0;
}