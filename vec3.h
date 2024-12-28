#ifndef VEC3_H
#define VEC3_H



namespace math{

    struct vec3
    {
        float x;
        float y;
        float z;


        vec3()
        {
            x = 1.0f;
            y = 1.0f;
            z = 1.0f;
        }
        vec3(float _x, float _y)
        {
            x = _x;
            y = _y;
            z = 1.0f;
        }
    };

}


#endif // VEC3_H
