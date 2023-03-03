#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

typedef struct BMPHeader{     // Total: 54 bytes
  uint8_t  type[2];           // Magic identifier: 0x4d42
  uint32_t  size;             // File size in bytes
  uint32_t  tresh;            // Not used
  uint32_t  offset;           // Offset to image data in bytes from beginning of InputFile (54 bytes)
}BMPHeader;

typedef struct BMPInfoHeader
{
  uint32_t  header_size;      // DIB Header size in bytes (40 bytes)
  uint32_t   width_px;        // Width of the image
  uint32_t   height_px;       // Height of image
  uint16_t  num_planes;       // Number of color planes
  uint16_t  bits_per_pixel;   // Bits per pixel
  uint32_t  compression;      // Compression type
  uint32_t  image_size_bytes; // Image size in bytes
  int32_t   x_resolution_ppm; // Pixels per meter
  int32_t   y_resolution_ppm; // Pixels per meter
  uint32_t  num_colors;       // Number of colors  
  uint32_t  important_colors; // Important colors 
} BMPInfoHeader;

typedef struct COLOR
{
    BYTE blue;
    BYTE green;
    BYTE red;
}COLOR;

//FUNCTIONS
void grayscale(int height , int width , COLOR color[height][width]);
void BmpReader(FILE *file);
void BmpWriter(FILE *file);
void ReadColor(int height , int width , COLOR color[height][width] , FILE *file , int padding);
void WriteColor(int height , int width , COLOR color[height][width] , FILE *file , int padding);
void PrintAscci(int height , int width , COLOR color[height][width] , int TerminalColor );
void PrintTXT(int height , int width , COLOR color[height][width] , FILE *file , int TXTcolor);

//HEADERS
BMPHeader Header;
BMPInfoHeader InfoHeader;

int main(int argc, char *argv[])
{
    //Check Arguments
    if (argc < 3 || strcmp(argv[1] ,"-i") != 0)
    {
        printf("Usage: ./painter -i InputFile");
        return 1;
    }
    //Open Input File
    FILE *InputFile = fopen(argv[2], "rb");

    if (InputFile == NULL)
    {
            printf("can't open the InputFile");
            return 1;
    }
    if (argc == 4)
    {
        printf("Usage: ./painter -i InputFile -o OutputFile");
        return 1;
    }
    if (argc == 5)
    {
        if (strcmp(argv[3] , "-o") != 0)
        {
            printf("Usage: ./painter -i InputFile -o OutputFile");
            return 1;
        }

        FILE *OutputFile = fopen(argv[4], "wb");

        if (OutputFile == NULL)
        {
            printf("can't open the OutputFile");
            return 1;
        }

        BmpReader(InputFile);

        //check for our requirement
        if (Header.type[0] != 'B' && Header.type[1] != 'M')
        {
            printf("I cant load this InputFile it need to start with BM");
            fclose(InputFile);
            return 1;
        }

        if (InfoHeader.compression != 0 || InfoHeader.header_size != 40 || InfoHeader.bits_per_pixel != 24 )
        {
            printf("I cant load this InputFile it need to be 24 bit color bmp InputFile");
            fclose(InputFile);
            return 1;
        }
        //write BMPHeader 

        //BmpWriter(OutputFile);
        //bitmap start
        fseek(InputFile, Header.offset, SEEK_SET);

        //padding 
        int rowSize = ((InfoHeader.bits_per_pixel * InfoHeader.width_px + 31 ) / 32) * 4;
        int padding = rowSize - InfoHeader.width_px * 3;

        //copy 
        COLOR colors[InfoHeader.height_px][InfoHeader.width_px];

        ReadColor(InfoHeader.height_px , InfoHeader.width_px , colors , InputFile , padding);

        grayscale(InfoHeader.height_px , InfoHeader.width_px , colors);

        PrintTXT(InfoHeader.height_px , InfoHeader.width_px , colors , OutputFile , padding);

        fclose(InputFile);
        fclose(OutputFile);
        return 0;
    }   
    //Open Output File

    // read BMPHeader
    BmpReader(InputFile);

    //check for our requirement
    if (Header.type[0] != 'B' && Header.type[1] != 'M')
    {
        printf("I cant load this InputFile it need to start with BM");
        fclose(InputFile);
        return 1;
    }

    if (InfoHeader.compression != 0 || InfoHeader.header_size != 40 || InfoHeader.bits_per_pixel != 24 )
    {
        printf("I cant load this InputFile it need to be 24 bit color bmp InputFile");
        fclose(InputFile);
        return 1;
    }
    //write BMPHeader 
    
    //bitmap start
    fseek(InputFile, Header.offset, SEEK_SET);

    //padding 
    int rowSize = ((InfoHeader.bits_per_pixel * InfoHeader.width_px + 31 ) / 32) * 4;
    int padding = rowSize - InfoHeader.width_px * 3;

    //copy 
    COLOR colors[InfoHeader.height_px][InfoHeader.width_px];

    ReadColor(InfoHeader.height_px , InfoHeader.width_px , colors , InputFile , padding);
    
    grayscale(InfoHeader.height_px , InfoHeader.width_px , colors);

    PrintAscci(InfoHeader.height_px , InfoHeader.width_px , colors , 0 );

    fclose(InputFile);
    return 0;
}

void grayscale(int height , int width , COLOR color[height][width])
{
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            int GrayColor = (color[i][j].red + color[i][j].green + color[i][j].blue) / 3;
            color[i][j].red = GrayColor;
            color[i][j].green = GrayColor;
            color[i][j].blue = GrayColor;
        }
    }
}

void BmpReader(FILE *file)
{
    fread(&Header.type, 2, 1 , file);
    fread(&Header.size, 3*sizeof(int), 1 , file);
    fread(&InfoHeader, sizeof(BMPInfoHeader), 1, file);
}

void BmpWriter(FILE *file)
{
    fwrite(&Header.type, 2, 1 , file);
    fwrite(&Header.size, 3 * sizeof(int), 1 , file);
    fwrite(&InfoHeader , sizeof(InfoHeader), 1 ,file);
}

void ReadColor(int height , int width , COLOR color[height][width] , FILE *file , int padding)
{
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            fread (&color[i][j], sizeof(COLOR), 1, file);
        }
        if(padding != 0)
        {
            char *buffer = malloc(sizeof(char) * padding);
            fread(buffer , padding , 1 ,file);
        }
    }
}

void WriteColor(int height , int width , COLOR color[height][width] , FILE *file , int padding)
{
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            fwrite (&color[i][j], sizeof(COLOR), 1, file);
        }
        if(padding != 0)
        {
            char *buffer = malloc(sizeof(char) * padding);
            fwrite(buffer , padding , 1 , file);
        }
    }
}

void PrintAscci(int height , int width , COLOR color[height][width] , int TerminalColor )
{
    char ascii1[] = {'@','#','W','$','9','8','7','6','5','4','3','2','1','0','?','!','a','b','c',';',';','+','=','-',',','.','_'};
    char ascii2[] = {'_','.',',','-','=','+',';',';','c','b','a','!','?','0','1','2','3','4','5','6','7','8','9','$','W','#','@'};

    for (int i = InfoHeader.height_px - 1; i >= 0; i--)
    {
        for (int j = 0; j < InfoHeader.width_px; j++)
        {
            int number = color[i][j].red;
            number = number / 9;
            if ( TerminalColor = 0 )
            {
                printf("%c  ", ascii2[number]);
            }
            else
            {
                printf("%c  ", ascii1[number]);
            }
        }
        printf("\n");
    }
}

void PrintTXT(int height , int width , COLOR color[height][width] , FILE *file , int TXTcolor)
{
    char ascii1[] = {'@','#','W','$','9','8','7','6','5','4','3','2','1','0','?','!','a','b','c',';',';','+','=','-',',','.','_'};
    char ascii2[] = {'_','.',',','-','=','+',';',';','c','b','a','!','?','0','1','2','3','4','5','6','7','8','9','$','W','#','@'};

    for (int i = height - 1 ; i >= 0 ; i--)
    {
        for (int j = 0; j < width ; j++)
        {
            int number = color[i][j].red;
            number = number / 9;
            if ( TXTcolor = 0)
            {
                fprintf(file,"%c  " , ascii2[number]);
            }
            else
            {
                fprintf(file,"%c  " , ascii1[number]);
            }
        }
        fprintf(file,"\n");
    }
}