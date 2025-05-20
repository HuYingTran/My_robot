#ifndef SETTINGS_H
#define SETTINGS_H

#define ERR_CALIB 3 //deg

typedef {
    STOP = 0,
    RUN = 1,
} robot_status_t;

typedef {
    ERR_POWER = 0,
    ERR_WIFI = 1,
}

typedef {
    float x, y, r;
    float a, g;     // Goc va van toc hien tai

} robot_t;

robot_t My_robot;

#endif