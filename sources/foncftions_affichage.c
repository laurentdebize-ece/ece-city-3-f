//
// Created by eleuc on 28/10/2022.
//

#include "../includes/foncftions_affichage.h"

void DrawGrid2(int slices, float spacing, Vector3 position)
{
    int halfSlices = slices/2;

    rlBegin(RL_LINES);
    for (int i = -halfSlices; i <= halfSlices; i++)
    {
        if (i == 0)
        {
            rlColor3f(0.5f, 0.5f, 0.5f);
            rlColor3f(0.5f, 0.5f, 0.5f);
            rlColor3f(0.5f, 0.5f, 0.5f);
            rlColor3f(0.5f, 0.5f, 0.5f);
        }
        else
        {
            rlColor3f(0, 0, 0);
            rlColor3f(0, 0, 0);
            rlColor3f(0, 0, 0);
            rlColor3f(0, 0, 0);
        }

        rlVertex3f((float)i*spacing + position.x, 0.0f + position.y, (float)-halfSlices*spacing + position.z);
        rlVertex3f((float)i*spacing + position.x, 0.0f + position.y, (float)halfSlices*spacing + position.z);

        rlVertex3f((float)-halfSlices*spacing + position.x, 0.0f + position.y, (float)i*spacing + position.z);
        rlVertex3f((float)halfSlices*spacing + position.x, 0.0f + position.y, (float)i*spacing + position.z);
    }
    rlEnd();
}