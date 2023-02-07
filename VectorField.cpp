#include "VectorField.h"

//static double gravFieldStrength = 0;

double VectorField::GetG()
{
    return G;
}

double VectorField::GetM()
{
    return M;
}

Vector3 VectorField::SamplePoint(Vector3* v, double* attractorFieldStrength)
{
    //gravetational field component
    double mag = Vector3::CalcLength(*v);
    Vector3 dir = Vector3::Normalize(*v, mag);

    *attractorFieldStrength = (-G * M) / (mag * mag);

    Vector3 acceleration = (*attractorFieldStrength) * dir;

    //Spin field component###################################

    //double tStrength = (T * S) / (mag * mag);

    //Vector3 preRot = Vector3::Scale(tStrength, dir);

    //acceleration = acceleration + Vector3(preRot.y, -preRot.x, preRot.z); //rotate vectors the lazy way!

    //acceleration = Vector3(0.0);

    /*acceleration.x = sin(((*v).x) / 100.0);
    acceleration.y = cos(((*v).y) / 100.0);
    acceleration.z = sin(((*v).z) / 100.0);*/

    return acceleration;
}