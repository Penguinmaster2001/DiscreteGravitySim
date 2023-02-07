#include "Main.h"

//resolution
int width  = 4000;
int height = 2000;
int frames = 1;
int threadWidth = 400;
int threadHeight = 200;

int threadsOnX = 8;
int threadsOnY = 8;

//Vector3 colors[width][height] = {  };

std::vector< std::vector< Vector3 > > finalPixel;

Background bg;

//accuracy
int simSteps = 1000000;
double simTimeStep = 0.01;

Vector3 cameraPos = Vector3(300, 0, 0);
Vector3 cameraDeltaPos = Vector3(-10.0, 0, 0);

std::string backgroundBmpPath = "no background path set";

std::string outputPath = "no output path set";
std::string outputName = "no name set";

std::string instructionPath = "no path set";

void SimThread(int threadX, int threadY, unsigned int threadWidth, unsigned int ThreadHeight)
{
    int startX = threadX * threadWidth;
    int startY = threadY * threadHeight;

    int endX = startX + threadWidth > width ? width : startX + threadWidth;
    int endY = startY + threadHeight > height ? height : startY + threadHeight;

    ParticleEmitter pe = ParticleEmitter(cameraPos, width, height, startX, endX, startY, endY, simSteps, simTimeStep, bg, finalPixel);

    pe.EmitSpherical();

    //std::string doneText = std::to_string(threadX) + "," + std::to_string(threadY) + " is done\n";

    //std::cout << doneText;
}


void DoSim(int frame)
{
    finalPixel.resize(width);

    for (int x = 0; x < width; x++)
    {
        finalPixel[x].resize(height);
        for (int y = 0; y < height; y++)
        {
            finalPixel[x][y] = Vector3(0.0);
        }
    }

    std::vector< std::vector< std::thread > > threadArray;

    threadArray.resize(threadsOnX);

    for (int x = 0; x < threadsOnX; ++x)
    {
        threadArray[x].resize(threadsOnY);

        for (int y = 0; y < threadsOnY; ++y)
        {
            threadArray[x][y] = std::thread(SimThread, x, y, threadWidth, threadHeight);
        }
    }

    std::cout << "0%\n";
    for (int x = 0; x < threadsOnX; ++x)
    {
        for (int y = 0; y < threadsOnY; ++y)
        {
            threadArray[x][y].join();

            std::cout << ( double((x * threadsOnY) + y) / double(threadsOnX * threadsOnY) ) * 100.0 << "%\n";
        }
    }

    std::cout << "100%\nThreads finished\n";

    Image image(width, height);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            //image.SetColor(Color(colors[x][y].x, colors[x][y].y, colors[x][y].z), x, y);
            image.SetColor(Color(finalPixel[x][y].x, finalPixel[x][y].y, finalPixel[x][y].z), x, y);

            //std::cout << Vector3(colors[x][y].x / (float)255, colors[x][y].y / (float)255, colors[x][y].z / (float)255) << "\n";
        }
    }

    //std::string path = "C:/Users/Penguin/Desktop/imgCppTestLog/TestAnimation2Frame" + std::to_string(frame) + ".bmp";

    image.Export((outputPath + outputName + "_" + std::to_string(frame) + ".bmp").c_str()); //wen ur good at programming (⌐■_■)
}

void OdThreaded(std::string fullOutputName, std::vector<Vector3> positions, std::vector<Vector3> velocities, std::vector<Vector3> accelerations)
{
    OutputData od;
    od.ExportDataTxt(fullOutputName + ".csv", simTimeStep, positions, velocities, accelerations);
}

void TestParticle()
{
    long double pi = 3.141592653589793;
    long double halfPi = pi / 2.0;

    Particle testParticle = Particle(cameraPos, cameraDeltaPos);

    /*for (long double i = -pi + (halfPi / 1.41688491956); i < -pi + (halfPi / 1.4168849195); i += (pi / 1000000000000.0))
    {
        testParticle.SetPosVel(Vector3(1000.0, 0.0, 0.0), Vector3(sin(i), cos(i), 0.0));

    }*/

    testParticle.DoSteps(simSteps, simTimeStep);

    std::cout << "sim done\n";

    std::vector<Vector3> positionsPtr = testParticle.data.particlePositions;
    std::vector<Vector3> velocitiesPtr = testParticle.data.particleVelocities;
    std::vector<Vector3> accelerationsPtr = testParticle.data.particleAccelerations;

    long double simMaxX =  double(frames);
    long double simMinX = -double(frames);

    long double simMaxY =  double(frames);
    long double simMinY = -double(frames);

    long double widthScaleFactor  = width  / (simMaxX - simMinX);
    long double heightScaleFactor = height / (simMaxY - simMinY);

    std::string fullOutputName = outputPath + outputName;

    std::thread odThread = std::thread(OdThreaded, fullOutputName, positionsPtr, velocitiesPtr, accelerationsPtr);

    Image image = Image(width, height);
    image.FillImage(Color(0.0, 0.0, 0.0));

    int size = positionsPtr.size();

    for (int i = 0; i < size; ++i)
    {
        Vector3 simPos = positionsPtr[i];

        double simX = simPos.x;
        double simY = simPos.y;

        int pixelX = int((simMaxX + simX) * widthScaleFactor);
        int pixelY = int((simMaxY + simY) * heightScaleFactor);

        if (pixelX < width && pixelY < height && pixelX >= 0 && pixelY >= 0)
        {
            image.SetColor(Color(double(i) / double(size), 1.0, 1.0), pixelX, pixelY);
        }
    }

    std::cout << "pixels logged\n";
    image.Export((fullOutputName + "_X_Y.bmp").c_str());


    //repeating code like a boss
    image.FillImage(Color(0.0, 0.0, 0.0));
    for (int i = 0; i < size; ++i)
    {
        Vector3 simPos = positionsPtr[i];

        double simX = simPos.x;
        double simY = simPos.z;

        int pixelX = int((simMaxX + simX) * widthScaleFactor);
        int pixelY = int((simMaxY + simY) * heightScaleFactor);

        if (pixelX < width && pixelY < height && pixelX >= 0 && pixelY >= 0)
        {
            image.SetColor(Color(double(i) / double(size), 1.0, 1.0), pixelX, pixelY);
        }
    }

    std::cout << "pixels logged\n";
    image.Export((fullOutputName + "_X_Z.bmp").c_str());



    image.FillImage(Color(0.0, 0.0, 0.0));
    for (int i = 0; i < size; ++i)
    {
        Vector3 simPos = positionsPtr[i];

        double simX = simPos.y;
        double simY = simPos.z;

        int pixelX = int((simMaxX + simX) * widthScaleFactor);
        int pixelY = int((simMaxY + simY) * heightScaleFactor);

        if (pixelX < width && pixelY < height && pixelX >= 0 && pixelY >= 0)
        {
            image.SetColor(Color(double(i) / double(size), 1.0, 1.0), pixelX, pixelY);
        }
    }

    std::cout << "pixels logged\n";
    image.Export((fullOutputName + "_Y_Z.bmp").c_str());



    image.FillImage(Color(0.0, 0.0, 0.0));
    for (int i = 0; i < size; ++i)
    {
        Vector3 simPos = positionsPtr[i];
        heightScaleFactor = height / (double(size));

        double simX = simPos.x;

        int pixelX = int((simMaxX + simX) * widthScaleFactor);
        int pixelY = int(i * heightScaleFactor);

        if (pixelX < width && pixelY < height && pixelX >= 0 && pixelY >= 0)
        {
            image.SetColor(Color(1.0, 1.0, 1.0), pixelX, pixelY);
        }
    }

    std::cout << "pixels logged\n";
    image.Export((fullOutputName + "_X_T.bmp").c_str());



    image.FillImage(Color(0.0, 0.0, 0.0));
    for (int i = 0; i < size; ++i)
    {
        Vector3 simPos = positionsPtr[i];

        double simX = simPos.y;

        int pixelX = int((simMaxX + simX) * widthScaleFactor);
        int pixelY = int(i * heightScaleFactor);

        if (pixelX < width && pixelY < height && pixelX >= 0 && pixelY >= 0)
        {
            image.SetColor(Color(1.0, 1.0, 1.0), pixelX, pixelY);
        }
    }

    std::cout << "pixels logged\n";
    image.Export((fullOutputName + "_Y_T.bmp").c_str());

    odThread.join();
}

void RenderFrames()
{

    for (int frame = 0; frame < frames; frame++)
    {
        DoSim(frame);

        cameraPos = cameraDeltaPos + cameraPos;
    }
}

int main()
{    
    //get instructions from user
    std::cout << "Input instruction filepath\nNote: change \"\\\" to \"/\"\nAlso make sure it's a valid path or the program may do weird things\n";
    /*
    * Input instruction filepath
    * Note: change "\" to "/"
    * Also make sure it's a valid path or the program may do weird things
    * 
    */

    std::cin >> instructionPath;

    //read instruction file and set all values
    InterpretInput ii;
    ii.readFile(width, height, frames, backgroundBmpPath, outputPath, outputName, simSteps, simTimeStep, cameraPos.x, cameraPos.y, cameraPos.z, cameraDeltaPos.x, cameraDeltaPos.y, cameraDeltaPos.z, instructionPath);

    bg = Background(backgroundBmpPath);

    //get mode from user
    std::cout << "Input mode, A for animation, D for data\n";
    /*
    * Input mode, A for animation, D for data
    * 
    */

    char mode;
    std::cin >> mode;

    switch (mode)
    {
    case 'a':
    case 'A':
    case '0':
        //threadsOnX = ceil(double(width ) / double(threadWidth ));
        //threadsOnY = ceil(double(height) / double(threadHeight));

        threadWidth  = ceil(double(width ) / double(threadsOnX));
        threadHeight = ceil(double(height) / double(threadsOnY));

        RenderFrames();
        break;

    default:
        std::cout << "error\n" << mode << "\nis not a valid mode, defaulting to data mode\n";
        /*
        * error
        * **mode**
        * is not a valid mode, defaulting to data mode
        * 
        */
    case 'd':
    case 'D':
    case '1':
        TestParticle();
        break;
    }

    char dummyChar;
    std::cin >> dummyChar;

    return 420;
}