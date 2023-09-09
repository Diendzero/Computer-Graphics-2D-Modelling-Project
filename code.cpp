#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <math.h>
#include <Windows.h>
#define MAX_CHAR 128

class Point {
public:
    float x, y;

    Point operator&(const Point& rPoint) {
        x = rPoint.x;
        y = rPoint.y;
        return *this;
    }
};

// Define the point
Point abc[3];

// Define the size of PI
const double PI = acos(-1.0);

// The variables used in the whole project
float word_step = 1, word_2023_x = 450, match_step = 4, match_x = 160,
Fu_angle = 0, Fu_step = 1, fire_depth = -10, fire_depth2 = -10,
envelope_x_scale = 0.001, envelope_y_scale = 0.001, envelope_x_step = 0.005, envelope_y_step = 0.005,
envelope_angle = 0, envelope_angle_step = 3.6, envelope_content = -10, envelope_content_step = 0.1,
envelope_left_part_x = 0, envelope_right_part_x = 0, envelope_left_part_x_step = 10, envelope_right_part_x_step = 10,
envelope_letter_x1 = 0, envelope_letter_x1_step = 0, envelope_letter_x2 = 0, envelope_letter_x2_step = 0, envelope_letter_x2_step_accelerate = 20,
envelope_letter_x_scale = 1, envelope_letter_y_scale = 1, envelope_letter_x_scale_step = 0.01, envelope_letter_y_scale_step = 0.01,
white_background_x = 0, white_background_x_step = 10;

// Set the refresh interval in ms
float time_interval1 = 30, time_interval2 = 30, time_interval3 = 15,
time_interval_envelope = 10, time_interval_envelope_tear = 30, time_interval_showCard = 30;

// Define the Bessel curve
Point drawBezier(Point A, Point B, Point C, double t) {
    Point P;
    P.x = pow((1 - t), 2) * A.x + 2 * t * (1 - t) * B.x + pow(t, 2) * C.x;
    P.y = pow((1 - t), 2) * A.y + 2 * t * (1 - t) * B.y + pow(t, 2) * C.y;
    return P;
}

// The drawLine method
void drawLine(Point p1, Point p2) {
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

// Idle callback function
void when_in_mainloop() {
    // force OpenGL to redraw the current window
    glutPostRedisplay();
}

// The animation of the number '2023'
void OnTimer_number_2023(int value) {
    word_2023_x += word_step;

    if (word_2023_x >= 470)
        word_step = -1;

    if (word_2023_x <= 420)
        word_step = 1;

    glutTimerFunc(time_interval1, OnTimer_number_2023, 1);
}

// The animation of the match
void OnTimer_match(int value) {
    match_x -= match_step;

    if (match_x > -92) {
        match_step = 4;
    }
    if (match_x <= -92 && match_x > -92.3) {
        match_step = 0.005;
        fire_depth = 1;
    }
    if (match_x <= -92.3 && match_x > -660) {
        match_step = 4;
    }
    if (match_x <= -660 && match_x > -660.4) {
        match_step = 0.002;
        fire_depth2 = 1;
    }
    if (match_x <= -660.4) {
        match_step = 4;
    }

    glutTimerFunc(time_interval2, OnTimer_match, 1);
}

// The animation of the word 'Fu'
void OnTimer_FuWord(int value) {
    Fu_angle += Fu_step;

    if (Fu_angle < 180) {
        Fu_step = 1;
    }
    if (Fu_angle >= 180 && Fu_angle <= 180.5) {
        Fu_step = 0.001;
    }
    if (Fu_angle > 180.3 && Fu_angle <= 359.6) {
        Fu_step = 1;
    }
    if (Fu_angle > 539.6 && Fu_angle < 360) {
        Fu_step = 0.001;
    }
    if (Fu_angle >= 360) {
        Fu_step = 1;
        Fu_angle = 0;
    }

    glutTimerFunc(time_interval3, OnTimer_FuWord, 1);
}

// The animation of the envelope
void onTimer_envelope(int value) {
    envelope_x_scale += envelope_x_step, envelope_y_scale += envelope_y_step;
    envelope_angle += envelope_angle_step;

    if (envelope_x_scale >= 1 && envelope_y_scale >= 1 && envelope_angle >= 360) {
        envelope_x_step = 0; envelope_y_step = 0; envelope_angle_step = 0;
        envelope_content += envelope_content_step;
    }

    glutTimerFunc(time_interval_envelope, onTimer_envelope, 1);
}

// The animation of tearing the envelope
void onTimer_envelope_tear(int value) {
    envelope_left_part_x -= envelope_left_part_x_step;
    envelope_right_part_x += envelope_right_part_x_step;
    envelope_letter_x1 += envelope_letter_x1_step;
    envelope_letter_x2 -= envelope_letter_x2_step;

    if (envelope_left_part_x <= -80) {
        envelope_left_part_x_step = 0;
    }

    if (envelope_right_part_x >= 300) {
        envelope_right_part_x_step = 0;
        envelope_letter_x1_step = 25;
        if (envelope_letter_x1 >= 1000) {
            envelope_letter_x1_step = 0;
            envelope_letter_x2_step = envelope_letter_x2_step_accelerate;
            envelope_letter_x2_step_accelerate -= 0.22;
        }
    }

    if (envelope_letter_x2 <= -885) {
        envelope_letter_x2_step = 0;
        envelope_letter_x_scale += envelope_letter_x_scale_step;
        envelope_letter_y_scale += envelope_letter_y_scale_step;
        if (envelope_letter_x_scale >= 1.5 && envelope_letter_y_scale >= 1.5) {
            envelope_letter_x_scale_step = 0;
            envelope_letter_y_scale_step = 0;
        }
    }

    glutTimerFunc(time_interval_envelope_tear, onTimer_envelope_tear, 1);
}

// The animation of show the new year card
void onTimer_showCard(int value) {
    white_background_x_step = 20;
    envelope_left_part_x_step = 5;
    envelope_letter_x2_step = 5;
    white_background_x -= white_background_x_step;
    envelope_left_part_x -= envelope_left_part_x_step;
    envelope_letter_x2 -= envelope_letter_x2_step;

    glutTimerFunc(time_interval_showCard, onTimer_showCard, 1);
}

// Mouse interaction
void mouse_input(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        onTimer_envelope_tear(1);
    }

    if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
        onTimer_showCard(1);
    }
}

// Keyboard interaction
void keyboard_input(unsigned char key, int x, int y) {
    if (key == 'q' || key == 'Q')
        exit(0);

    if (key == 'l' || key == 'L')
        OnTimer_match(1);
}

// The method of writing words
void drawString(const char* str) {
    int len, i;
    wchar_t* wstring;
    HDC hDC = wglGetCurrentDC();
    GLuint list = glGenLists(1);
    len = 0;
    for (i = 0; str[i] != '\0'; ++i)
    {
        if (IsDBCSLeadByte(str[i]))
            ++i;
        ++len;
    }
    wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
    wstring[len] = L'\0';
    for (i = 0; i < len; ++i)
    {
        wglUseFontBitmapsW(hDC, wstring[i], 1, list);
        glCallList(list);
    }
    free(wstring);
    glDeleteLists(list, 1);
}

// The method of setting different fonts and sizes
void setFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hPreviousFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hPreviousFont);
}

// The method of drawing the word 'HAPPY CHINESE'
void drawWord1(void) {
    glLoadIdentity();

    glColor3ub(255, 222, 173);
    setFont(30, ANSI_CHARSET, "Bodoni MT");
    glRasterPos2f(385, 140);
    drawString(" HAPPY CHINESE");
}

// The method of drawing the word 'NEW YEAR'
void drawWord2(void) {
    glLoadIdentity();

    glColor3ub(255, 222, 173);
    setFont(50, ANSI_CHARSET, "Imprint MT Shadow");
    glRasterPos2f(370, 90);
    drawString("NEW YEAR");
}

// The method of drawing the number '2023'
void drawWord3(void) {
    glLoadIdentity();

    glColor3ub(220, 149, 76);
    setFont(52, GB2312_CHARSET, "Imprint MT Shadow");
    glRasterPos2f(word_2023_x, 40);
    drawString("2023");
}

// The method of drawing the frame of card
void drawFrame(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    glColor3ub(255, 198, 166);
    glLineWidth(2);
    GLfloat
        Point1[2] = { 75, 30 }, Point2[2] = { 75, 60 }, Point3[2] = { 45, 60 },
        Point4[2] = { 45, 15 }, Point5[2] = { 60, 15 }, Point6[2] = { 60, 30 },
        Point7[2] = { 15, 30 }, Point8[2] = { 15, 15 }, Point9[2] = { 30, 15 },
        Point10[2] = { 30, 60 }, Point11[2] = { 15, 60 }, Point12[2] = { 15, 45 },
        Point13[2] = { 60, 45 }, Point14[2] = { 60, 75 }, Point57[2] = { 955, 15 },
        Point15[2] = { 30, 75 }, Point16[2] = { 30, 725 }, Point17[2] = { 60, 725 },
        Point18[2] = { 60, 755 }, Point19[2] = { 15, 755 }, Point20[2] = { 15, 740 },
        Point21[2] = { 30, 740 }, Point22[2] = { 30, 785 }, Point23[2] = { 15, 785 },
        Point24[2] = { 15, 770 }, Point25[2] = { 60, 770 }, Point26[2] = { 60, 785 },
        Point27[2] = { 45, 785 }, Point28[2] = { 45, 740 }, Point29[2] = { 75, 740 },
        Point30[2] = { 75, 770 }, Point31[2] = { 925, 770 }, Point32[2] = { 925, 740 },
        Point33[2] = { 955, 740 }, Point34[2] = { 955, 785 }, Point35[2] = { 940, 785 },
        Point36[2] = { 940, 770 }, Point37[2] = { 985, 770 }, Point38[2] = { 985, 785 },
        Point39[2] = { 970, 785 }, Point40[2] = { 970, 740 }, Point41[2] = { 985, 740 },
        Point42[2] = { 985, 755 }, Point43[2] = { 940, 755 }, Point44[2] = { 940, 725 },
        Point45[2] = { 970, 725 }, Point46[2] = { 970, 75 }, Point47[2] = { 940, 75 },
        Point48[2] = { 940, 45 }, Point49[2] = { 985, 45 }, Point50[2] = { 985, 60 },
        Point51[2] = { 970, 60 }, Point52[2] = { 970, 15 }, Point53[2] = { 985, 15 },
        Point54[2] = { 985, 30 }, Point55[2] = { 940, 30 }, Point56[2] = { 940, 15 },
        Point58[2] = { 955, 60 }, Point59[2] = { 925, 60 }, Point60[2] = { 925, 30 };

    glBegin(GL_LINE_LOOP);
    glVertex2fv(Point1); glVertex2fv(Point2); glVertex2fv(Point3); glVertex2fv(Point4);
    glVertex2fv(Point5); glVertex2fv(Point6); glVertex2fv(Point7); glVertex2fv(Point8);
    glVertex2fv(Point9); glVertex2fv(Point10); glVertex2fv(Point11); glVertex2fv(Point12);
    glVertex2fv(Point13); glVertex2fv(Point14); glVertex2fv(Point15); glVertex2fv(Point16);
    glVertex2fv(Point17); glVertex2fv(Point18); glVertex2fv(Point19); glVertex2fv(Point20);
    glVertex2fv(Point21); glVertex2fv(Point22); glVertex2fv(Point23); glVertex2fv(Point24);
    glVertex2fv(Point25); glVertex2fv(Point26); glVertex2fv(Point27); glVertex2fv(Point28);
    glVertex2fv(Point29); glVertex2fv(Point30); glVertex2fv(Point31); glVertex2fv(Point32);
    glVertex2fv(Point33); glVertex2fv(Point34); glVertex2fv(Point35); glVertex2fv(Point36);
    glVertex2fv(Point37); glVertex2fv(Point38); glVertex2fv(Point39); glVertex2fv(Point40);
    glVertex2fv(Point41); glVertex2fv(Point42); glVertex2fv(Point43); glVertex2fv(Point44);
    glVertex2fv(Point45); glVertex2fv(Point46); glVertex2fv(Point47); glVertex2fv(Point48);
    glVertex2fv(Point49); glVertex2fv(Point50); glVertex2fv(Point51); glVertex2fv(Point52);
    glVertex2fv(Point53); glVertex2fv(Point54); glVertex2fv(Point55); glVertex2fv(Point56);
    glVertex2fv(Point57); glVertex2fv(Point58); glVertex2fv(Point59); glVertex2fv(Point60);
    glEnd();
}

void drawBranch1(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    // Set the color of line
    glColor3ub(40, 38, 38);

    abc[0] = { 0, 535 };
    abc[1] = { 67, 553 };
    abc[2] = { 110, 620 };
    Point POld = abc[0];
    glLineWidth(15);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 110, 620 };
    abc[1] = { 159, 691 };
    abc[2] = { 429, 751 };
    POld = abc[0];
    glLineWidth(15);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    // Rounded trim at the end of branch 1
    glTranslatef(0.86, 1.878, 0);
    float R = 8.5;
    int n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawBranch2(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    // Set the color of line
    glColor3ub(40, 38, 38);

    // Branch 2
    abc[0] = { 25, 548 };
    abc[1] = { 58, 550 };
    abc[2] = { 99, 537 };
    Point POld = abc[0];
    glLineWidth(6.5);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 99, 537 };
    abc[1] = { 179, 533 };
    abc[2] = { 228, 582 };
    POld = abc[0];
    glLineWidth(6.5);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    // Rounded trim at the end of branch 2
    glTranslatef(0.45, 1.448, 0);
    float R = 5;
    int n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawBranch3(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    // Set the color of line
    glColor3ub(40, 38, 38);

    // Branch 3_1
    abc[0] = { 130, 646 };
    abc[1] = { 253, 681 };
    abc[2] = { 342, 655 };
    Point POld = abc[0];
    glLineWidth(9);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 342, 655 };
    abc[1] = { 372, 648 };
    abc[2] = { 385, 627 };
    POld = abc[0];
    glLineWidth(8);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
}

void drawBranch4(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    // Set the color of line
    glColor3ub(40, 38, 38);

    // Branch 4
    abc[0] = { 192, 681 };
    abc[1] = { 219, 715 };
    abc[2] = { 224, 744 };
    Point POld = abc[0];
    glLineWidth(5);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
}

void drawBranch5(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    // Set the color of line
    glColor3ub(40, 38, 38);

    // Branch 5_1
    abc[0] = { 297, 722 };
    abc[1] = { 411, 683 };
    abc[2] = { 516, 724 };
    Point POld = abc[0];
    glLineWidth(9);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    // Branch 5_2
    abc[0] = { 443, 708 };
    abc[1] = { 478, 693 };
    abc[2] = { 523, 690 };
    POld = abc[0];
    glLineWidth(6);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
}

void drawLantern1(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glColor3ub(255, 216, 172);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(152, 545);
    glVertex2f(152, 465);
    glEnd();

    glColor3ub(207, 153, 74);
    glLineWidth(3);
    abc[0] = { 130, 455 };
    abc[1] = { 153, 480 };
    abc[2] = { 173, 455 };
    Point POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    glBegin(GL_POLYGON);
    glVertex2f(120, 455);
    glVertex2f(183, 455);
    glVertex2f(183, 445);
    glVertex2f(120, 445);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(120, 355);
    glVertex2f(183, 355);
    glVertex2f(183, 345);
    glVertex2f(120, 345);
    glEnd();

    glColor3ub(255, 216, 172);
    glLineWidth(2.5);
    abc[0] = { 122, 345 };
    abc[1] = { 122, 320 };
    abc[2] = { 110, 279 };
    POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    glColor3ub(255, 216, 172);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(131, 345);
    glVertex2f(131, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(141, 345);
    glVertex2f(141, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(151, 345);
    glVertex2f(151, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(161, 345);
    glVertex2f(161, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(171, 345);
    glVertex2f(171, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(181, 345);
    glVertex2f(181, 279);
    glEnd();

    glColor3ub(161, 38, 125);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(152, 445);
    glVertex2f(152, 355);
    glEnd();
    glLineWidth(3);
    abc[0] = { 136, 445 };
    abc[1] = { 120, 406 };
    abc[2] = { 136, 355 };
    POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 125, 445 };
    abc[1] = { 90, 406 };
    abc[2] = { 125, 355 };
    POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 168, 445 };
    abc[1] = { 184, 406 };
    abc[2] = { 168, 355 };
    POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 179, 445 };
    abc[1] = { 214, 406 };
    abc[2] = { 179, 355 };
    POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    glColor3ub(174, 44, 143);
    glTranslatef(0.303, 0.999, 0);
    float R = 55;
    int n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawLantern2(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glColor3ub(255, 216, 172);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(263, 671);
    glVertex2f(263, 585);
    glEnd();

    glTranslatef(0.223, 0.29, 0);

    glColor3ub(207, 153, 74);
    glLineWidth(3);
    abc[0] = { 130, 455 };
    abc[1] = { 153, 480 };
    abc[2] = { 173, 455 };
    Point POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    glBegin(GL_POLYGON);
    glVertex2f(120, 455);
    glVertex2f(183, 455);
    glVertex2f(183, 445);
    glVertex2f(120, 445);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(120, 355);
    glVertex2f(185, 355);
    glVertex2f(185, 345);
    glVertex2f(120, 345);
    glEnd();

    glColor3ub(255, 216, 172);
    glLineWidth(2.5);
    abc[0] = { 122, 345 };
    abc[1] = { 122, 320 };
    abc[2] = { 110, 279 };
    POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    glColor3ub(255, 216, 172);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(131, 345);
    glVertex2f(131, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(141, 345);
    glVertex2f(141, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(151, 345);
    glVertex2f(151, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(161, 345);
    glVertex2f(161, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(171, 345);
    glVertex2f(171, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(181, 345);
    glVertex2f(181, 279);
    glEnd();

    glColor3ub(108, 164, 140);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(97, 401);
    glVertex2f(205, 401);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(99, 412);
    glVertex2f(204, 412);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(103, 424);
    glVertex2f(199, 424);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(110, 435);
    glVertex2f(192, 435);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(99, 390);
    glVertex2f(204, 390);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(103, 378);
    glVertex2f(200, 378);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(110, 367);
    glVertex2f(193, 367);
    glEnd();

    glColor3ub(125, 183, 160);
    glTranslatef(0.303, 0.999, 0);
    float R = 55;
    int n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();

    glDisable(GL_DEPTH_TEST);
    glColor3ub(213, 154, 67);
    float R1 = 35;
    float R2 = 22;
    int n1 = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R1 * cos(2 * PI * i / n1), R2 * sin(2 * PI * i / n1));
    }
    glEnd();
}

void drawLantern3(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.55, 0.4, 0);

    glColor3ub(255, 216, 172);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(152, 545);
    glVertex2f(152, 390);
    glEnd();

    glTranslatef(0, -0.19, 0);

    glColor3ub(207, 153, 74);
    glLineWidth(3);
    abc[0] = { 130, 455 };
    abc[1] = { 153, 480 };
    abc[2] = { 173, 455 };
    Point POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    glBegin(GL_POLYGON);
    glVertex2f(120, 455);
    glVertex2f(183, 455);
    glVertex2f(183, 445);
    glVertex2f(120, 445);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(120, 355);
    glVertex2f(183, 355);
    glVertex2f(183, 345);
    glVertex2f(120, 345);
    glEnd();

    glColor3ub(255, 216, 172);
    glLineWidth(2.5);
    abc[0] = { 122, 345 };
    abc[1] = { 122, 320 };
    abc[2] = { 110, 279 };
    POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    glColor3ub(255, 216, 172);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(131, 345);
    glVertex2f(131, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(141, 345);
    glVertex2f(141, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(151, 345);
    glVertex2f(151, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(161, 345);
    glVertex2f(161, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(171, 345);
    glVertex2f(171, 279);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(181, 345);
    glVertex2f(181, 279);
    glEnd();

    glColor3ub(148, 32, 62);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(108, 402);
    glVertex2f(197, 402);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(108, 415);
    glVertex2f(197, 415);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(108, 428);
    glVertex2f(197, 428);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(108, 389);
    glVertex2f(197, 389);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(108, 376);
    glVertex2f(197, 376);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glColor3ub(154, 35, 68);
    // Rounded rectangle left and right shading
    glBegin(GL_POLYGON);
    glVertex2f(107, 430);
    glVertex2f(198, 430);
    glVertex2f(198, 371);
    glVertex2f(107, 371);
    glEnd();
    // Rounded rectangles with top and bottom shading
    glBegin(GL_POLYGON);
    glVertex2f(120, 445);
    glVertex2f(183, 445);
    glVertex2f(183, 345);
    glVertex2f(120, 345);
    glEnd();
    glTranslatef(0.244, 1.074, 0);
    // Drawing of the four rounded corners of a rounded rectangle
    float R1 = 15;
    int n1 = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n1; i++) {
        glVertex2f(R1 * cos(2 * PI * i / n1), R1 * sin(2 * PI * i / n1));
    }
    glEnd();
    glTranslatef(0.122, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n1; i++) {
        glVertex2f(R1 * cos(2 * PI * i / n1), R1 * sin(2 * PI * i / n1));
    }
    glEnd();
    glTranslatef(0, -0.148, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n1; i++) {
        glVertex2f(R1 * cos(2 * PI * i / n1), R1 * sin(2 * PI * i / n1));
    }
    glEnd();
    glTranslatef(-0.122, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n1; i++) {
        glVertex2f(R1 * cos(2 * PI * i / n1), R1 * sin(2 * PI * i / n1));
    }
    glEnd();
}

void drawLantern4(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.68, 0.6, 0);

    glColor3ub(255, 216, 172);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(175, 450);
    glVertex2f(175, 400);
    glEnd();

    glTranslatef(0.047, -0.17, 0);

    glColor3ub(207, 153, 74);
    glLineWidth(3);
    abc[0] = { 130, 455 };
    abc[1] = { 153, 480 };
    abc[2] = { 173, 455 };
    Point POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    glBegin(GL_POLYGON);
    glVertex2f(120, 455);
    glVertex2f(183, 455);
    glVertex2f(183, 445);
    glVertex2f(120, 445);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(120, 355);
    glVertex2f(183, 355);
    glVertex2f(183, 345);
    glVertex2f(120, 345);
    glEnd();

    glColor3ub(112, 165, 146);
    glBegin(GL_POLYGON);
    glVertex2f(183, 445);
    glVertex2f(120, 445);
    glVertex2f(120, 355);
    glVertex2f(183, 355);
    glEnd();

    glTranslatef(-0.0015, 0, 0);
    glDisable(GL_DEPTH_TEST);
    glColor3ub(199, 138, 65);
    glBegin(GL_TRIANGLES);
    glVertex2f(135, 440);
    glVertex2f(135, 360);
    glVertex2f(125, 400);
    glEnd();
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(140, 435);
    glVertex2f(140, 365);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(148, 435);
    glVertex2f(148, 365);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(156, 435);
    glVertex2f(156, 365);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(164, 435);
    glVertex2f(164, 365);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(170, 440);
    glVertex2f(170, 360);
    glVertex2f(180, 400);
    glEnd();
}

void drawLantern1Decoration(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glColor3ub(255, 216, 172);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(151, 280);
    glVertex2f(151, 265);
    glEnd();

    glColor3ub(255, 198, 166);
    glBegin(GL_TRIANGLES);
    glVertex2f(151, 255);
    glVertex2f(141, 210);
    glVertex2f(161, 210);
    glEnd();

    glTranslatef(0.302, 0.65, 0);
    glColor3ub(182, 137, 58);
    float R = 6;
    int n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawLantern3Decoration(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.55, 0.21, 0);
    glColor3ub(255, 216, 172);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(151, 280);
    glVertex2f(151, 265);
    glEnd();

    glColor3ub(255, 198, 166);
    glBegin(GL_TRIANGLES);
    glVertex2f(151, 255);
    glVertex2f(141, 210);
    glVertex2f(161, 210);
    glEnd();

    glTranslatef(0.302, 0.65, 0);
    glColor3ub(182, 137, 58);
    float R = 6;
    int n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawLantern4Decoration(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.728, 0.6, 0);
    glColor3ub(255, 216, 172);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(151, 280);
    glVertex2f(151, 265);
    glEnd();

    glColor3ub(255, 198, 166);
    glBegin(GL_TRIANGLES);
    glVertex2f(151, 255);
    glVertex2f(141, 210);
    glVertex2f(161, 210);
    glEnd();

    glTranslatef(0.302, 0.65, 0);
    glColor3ub(182, 137, 58);
    float R = 6;
    int n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFlower1(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glColor3ub(197, 115, 168);
    float R = 8;
    float n = 80;
    glTranslatef(0.08, 1.44, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glColor3ub(224, 201, 204);
    glTranslatef(0, 0.035, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.025, -0.024, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, -0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.03, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, 0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFlower2(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glColor3ub(197, 115, 168);
    float R = 8;
    float n = 80;
    glTranslatef(0.29, 1.56, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glColor3ub(224, 201, 204);
    glTranslatef(0, 0.035, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.025, -0.024, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, -0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.03, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, 0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFlower3(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.38, 1.4, 0);
    glColor3ub(197, 115, 168);
    float R = 8;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glColor3ub(224, 201, 204);
    glTranslatef(0, 0.035, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.025, -0.024, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, -0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.03, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, 0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFlower4(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.39, 1.8, 0);
    glColor3ub(197, 115, 168);
    float R = 8;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glColor3ub(224, 201, 204);
    glTranslatef(0, 0.035, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.025, -0.024, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, -0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.03, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, 0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFlower5(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.95, 1.85, 0);
    glColor3ub(197, 115, 168);
    float R = 8;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glColor3ub(224, 201, 204);
    glTranslatef(0, 0.035, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.025, -0.024, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, -0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.03, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, 0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFlower6(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(1.18, 1.8, 0);
    glColor3ub(197, 115, 168);
    float R = 8;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glColor3ub(224, 201, 204);
    glTranslatef(0, 0.035, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.025, -0.024, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, -0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.03, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, 0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFlower7(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.42, 1.62, 0);
    glColor3ub(197, 115, 168);
    float R = 10;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glColor3ub(224, 201, 204);
    glTranslatef(0, 0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.0285, -0.025, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.009, -0.045, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.036, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, 0.045, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFlower8(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.78, 1.75, 0);
    glColor3ub(197, 115, 168);
    float R = 10;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glColor3ub(224, 201, 204);
    glTranslatef(0, 0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.0285, -0.025, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.009, -0.045, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.036, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, 0.045, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFlower9(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.935, 1.665, 0);
    glColor3ub(197, 115, 168);
    float R = 10;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glColor3ub(224, 201, 204);
    glTranslatef(0, 0.038, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.0285, -0.025, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.009, -0.045, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.036, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.01, 0.045, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFlower10(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.57, 1.85, 0);
    glColor3ub(197, 115, 168);
    float R = 12;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glColor3ub(224, 201, 204);
    glTranslatef(0, 0.05, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.0365, -0.033, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.012, -0.055, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.044, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.015, 0.054, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFlower11(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(1.1, 1.68, 0);
    glColor3ub(197, 115, 168);
    float R = 6;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glColor3ub(224, 201, 204);
    glTranslatef(0, 0.025, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.019, -0.017, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.006, -0.029, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.023, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.008, 0.028, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFlower12(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(1.3, 1.71, 0);
    glColor3ub(197, 115, 168);
    float R = 6;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glColor3ub(224, 201, 204);
    glTranslatef(0, 0.025, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.019, -0.017, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.006, -0.029, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.023, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.008, 0.028, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawWordDecoration_star(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.02, 0.05, 0);

    glColor3ub(234, 153, 153);
    // Draw a pentagram
    glBegin(GL_POLYGON);
    glVertex2f(469, 240);
    glVertex2f(487, 240);
    glVertex2f(494, 224);
    glVertex2f(478, 209);
    glVertex2f(462, 224);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(478, 262);
    glVertex2f(469, 240);
    glVertex2f(487, 240);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(469, 240);
    glVertex2f(446, 238);
    glVertex2f(462, 224);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(462, 224);
    glVertex2f(458, 199);
    glVertex2f(478, 209);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(478, 209);
    glVertex2f(498, 199);
    glVertex2f(494, 224);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(494, 224);
    glVertex2f(510, 238);
    glVertex2f(487, 240);
    glEnd();
}

void drawWordDecoration_left1(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.02, 0.05, 0);

    glLineWidth(1.5);
    // left1
    abc[0] = { 454, 231 };
    abc[1] = { 457, 213 };
    abc[2] = { 437, 201 };
    Point POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 437, 201 };
    abc[1] = { 410, 188 };
    abc[2] = { 398, 223 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 398, 223 };
    abc[1] = { 407, 246 };
    abc[2] = { 418, 234 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 418, 234 };
    abc[1] = { 427, 226 };
    abc[2] = { 416, 216 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 416, 216 };
    abc[1] = { 405, 215 };
    abc[2] = { 405, 228 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 405, 228 };
    abc[1] = { 410, 236 };
    abc[2] = { 417, 228 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 417, 228 };
    abc[1] = { 413, 222 };
    abc[2] = { 410, 226 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    // left2
    glLineWidth(2.5);
    abc[0] = { 460, 226 };
    abc[1] = { 459, 166 };
    abc[2] = { 335, 177 };
    Point POld1 = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld1, P);
        POld1 = P;
    }
    abc[0] = { 335, 177 };
    abc[1] = { 289, 181 };
    abc[2] = { 279, 156 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld1, P);
        POld1 = P;
    }
}

void drawWordDecoration_left_leaves1(void) {
    glLoadIdentity();
    glTranslatef(0.02, 0.05, 0);

    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(422, 181);
    glVertex2f(413, 198);
    glVertex2f(401, 189);
    glEnd();
    abc[0] = { 413, 198 };
    abc[1] = { 399, 207 };
    abc[2] = { 401, 189 };
    Point POld2 = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(-0.05, -0.01, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(422, 181);
    glVertex2f(413, 198);
    glVertex2f(401, 189);
    glEnd();
    abc[0] = { 413, 198 };
    abc[1] = { 399, 207 };
    abc[2] = { 401, 189 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(-0.05, -0.005, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(422, 181);
    glVertex2f(413, 198);
    glVertex2f(401, 189);
    glEnd();
    abc[0] = { 413, 198 };
    abc[1] = { 399, 207 };
    abc[2] = { 401, 189 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(-0.06, 0.005, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(422, 181);
    glVertex2f(413, 198);
    glVertex2f(401, 189);
    glEnd();
    abc[0] = { 413, 198 };
    abc[1] = { 399, 207 };
    abc[2] = { 401, 189 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(-0.065, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(422, 181);
    glVertex2f(413, 198);
    glVertex2f(401, 189);
    glEnd();
    abc[0] = { 413, 198 };
    abc[1] = { 399, 207 };
    abc[2] = { 401, 189 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }
}

void drawWordDecoration_left_leaves2(void) {
    glLoadIdentity();

    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(443, 206);
    glVertex2f(425, 193);
    glVertex2f(436, 183);
    glEnd();
    abc[0] = { 425, 193 };
    abc[1] = { 414, 180 };
    abc[2] = { 436, 183 };
    Point POld2 = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(-0.05, -0.02, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(443, 206);
    glVertex2f(425, 193);
    glVertex2f(436, 183);
    glEnd();
    abc[0] = { 425, 193 };
    abc[1] = { 414, 180 };
    abc[2] = { 436, 183 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(-0.05, -0.005, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(443, 206);
    glVertex2f(425, 193);
    glVertex2f(436, 183);
    glEnd();
    abc[0] = { 425, 193 };
    abc[1] = { 414, 180 };
    abc[2] = { 436, 183 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(-0.05, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(443, 206);
    glVertex2f(425, 193);
    glVertex2f(436, 183);
    glEnd();
    abc[0] = { 425, 193 };
    abc[1] = { 414, 180 };
    abc[2] = { 436, 183 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(-0.06, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(443, 206);
    glVertex2f(425, 193);
    glVertex2f(436, 183);
    glEnd();
    abc[0] = { 425, 193 };
    abc[1] = { 414, 180 };
    abc[2] = { 436, 183 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }
}

void drawWordDecoration_left2(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glLineWidth(1.5);
    // left2
    abc[0] = { 379, 106 };
    abc[1] = { 348, 105 };
    abc[2] = { 328, 125 };
    Point POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
}

void drawWordDecoration_left_leaves3(void) {
    glLoadIdentity();

    glLineWidth(1.5);
    abc[0] = { 364, 107 };
    abc[1] = { 369, 118 };
    abc[2] = { 359, 121 };
    Point POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 359, 121 };
    abc[1] = { 350, 114 };
    abc[2] = { 364, 107 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glBegin(GL_LINES);
    glVertex2f(364, 107);
    glVertex2f(360, 117);
    glEnd();

    glTranslatef(-0.03, 0.015, 0);
    abc[0] = { 364, 107 };
    abc[1] = { 369, 118 };
    abc[2] = { 359, 121 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 359, 121 };
    abc[1] = { 350, 114 };
    abc[2] = { 364, 107 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glBegin(GL_LINES);
    glVertex2f(364, 107);
    glVertex2f(360, 117);
    glEnd();

    glTranslatef(-0.03, 0.02, 0);
    abc[0] = { 364, 107 };
    abc[1] = { 369, 118 };
    abc[2] = { 359, 121 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 359, 121 };
    abc[1] = { 350, 114 };
    abc[2] = { 364, 107 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glBegin(GL_LINES);
    glVertex2f(364, 107);
    glVertex2f(360, 117);
    glEnd();
}

void drawWordDecoration_left_leaves4(void) {
    glLoadIdentity();

    glLineWidth(1.5);
    abc[0] = { 364, 107 };
    abc[1] = { 368, 98 };
    abc[2] = { 355, 95 };
    Point POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 355, 95 };
    abc[1] = { 352, 106 };
    abc[2] = { 364, 107 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glBegin(GL_LINES);
    glVertex2f(364, 107);
    glVertex2f(358, 100);
    glEnd();

    glTranslatef(-0.035, 0.01, 0);
    abc[0] = { 364, 107 };
    abc[1] = { 368, 98 };
    abc[2] = { 355, 95 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 355, 95 };
    abc[1] = { 352, 106 };
    abc[2] = { 364, 107 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glBegin(GL_LINES);
    glVertex2f(364, 107);
    glVertex2f(358, 100);
    glEnd();

    glTranslatef(-0.028, 0.022, 0);
    abc[0] = { 364, 107 };
    abc[1] = { 368, 98 };
    abc[2] = { 355, 95 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 355, 95 };
    abc[1] = { 352, 106 };
    abc[2] = { 364, 107 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glBegin(GL_LINES);
    glVertex2f(364, 107);
    glVertex2f(358, 100);
    glEnd();
}

void drawWordDecoration_right1(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.02, 0.05, 0);

    glLineWidth(1.5);
    // right
    abc[0] = { 956 - 454, 231 };
    abc[1] = { 956 - 457, 213 };
    abc[2] = { 956 - 437, 201 };
    Point POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 956 - 437, 201 };
    abc[1] = { 956 - 410, 188 };
    abc[2] = { 956 - 398, 223 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 956 - 398, 223 };
    abc[1] = { 956 - 407, 246 };
    abc[2] = { 956 - 418, 234 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 956 - 418, 234 };
    abc[1] = { 956 - 427, 226 };
    abc[2] = { 956 - 416, 216 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 956 - 416, 216 };
    abc[1] = { 956 - 405, 215 };
    abc[2] = { 956 - 405, 228 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 956 - 405, 228 };
    abc[1] = { 956 - 410, 236 };
    abc[2] = { 956 - 417, 228 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 956 - 417, 228 };
    abc[1] = { 956 - 413, 222 };
    abc[2] = { 956 - 410, 226 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    // right2
    glLineWidth(2.5);
    abc[0] = { 956 - 460, 226 };
    abc[1] = { 956 - 459, 166 };
    abc[2] = { 956 - 335, 177 };
    Point POld1 = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld1, P);
        POld1 = P;
    }
    abc[0] = { 956 - 335, 177 };
    abc[1] = { 956 - 289, 181 };
    abc[2] = { 956 - 279, 156 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld1, P);
        POld1 = P;
    }
}

void drawWordDecoration_right_leaves1(void) {
    glLoadIdentity();
    glTranslatef(0.02, 0.05, 0);

    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(956 - 422, 181);
    glVertex2f(956 - 413, 198);
    glVertex2f(956 - 401, 189);
    glEnd();
    abc[0] = { 956 - 413, 198 };
    abc[1] = { 956 - 399, 207 };
    abc[2] = { 956 - 401, 189 };
    Point POld2 = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(0.05, -0.01, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(956 - 422, 181);
    glVertex2f(956 - 413, 198);
    glVertex2f(956 - 401, 189);
    glEnd();
    abc[0] = { 956 - 413, 198 };
    abc[1] = { 956 - 399, 207 };
    abc[2] = { 956 - 401, 189 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(0.05, -0.005, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(956 - 422, 181);
    glVertex2f(956 - 413, 198);
    glVertex2f(956 - 401, 189);
    glEnd();
    abc[0] = { 956 - 413, 198 };
    abc[1] = { 956 - 399, 207 };
    abc[2] = { 956 - 401, 189 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(0.06, 0.005, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(956 - 422, 181);
    glVertex2f(956 - 413, 198);
    glVertex2f(956 - 401, 189);
    glEnd();
    abc[0] = { 956 - 413, 198 };
    abc[1] = { 956 - 399, 207 };
    abc[2] = { 956 - 401, 189 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(0.065, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(956 - 422, 181);
    glVertex2f(956 - 413, 198);
    glVertex2f(956 - 401, 189);
    glEnd();
    abc[0] = { 956 - 413, 198 };
    abc[1] = { 956 - 399, 207 };
    abc[2] = { 956 - 401, 189 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }
}

void drawWordDecoration_right_leaves2(void) {
    glLoadIdentity();

    glTranslatef(0.045, 0, 0);
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(956 - 443, 206);
    glVertex2f(956 - 425, 193);
    glVertex2f(956 - 436, 183);
    glEnd();
    abc[0] = { 956 - 425, 193 };
    abc[1] = { 956 - 414, 180 };
    abc[2] = { 956 - 436, 183 };
    Point POld2 = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(0.05, -0.02, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(956 - 443, 206);
    glVertex2f(956 - 425, 193);
    glVertex2f(956 - 436, 183);
    glEnd();
    abc[0] = { 956 - 425, 193 };
    abc[1] = { 956 - 414, 180 };
    abc[2] = { 956 - 436, 183 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(0.05, -0.005, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(956 - 443, 206);
    glVertex2f(956 - 425, 193);
    glVertex2f(956 - 436, 183);
    glEnd();
    abc[0] = { 956 - 425, 193 };
    abc[1] = { 956 - 414, 180 };
    abc[2] = { 956 - 436, 183 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(0.05, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(956 - 443, 206);
    glVertex2f(956 - 425, 193);
    glVertex2f(956 - 436, 183);
    glEnd();
    abc[0] = { 956 - 425, 193 };
    abc[1] = { 956 - 414, 180 };
    abc[2] = { 956 - 436, 183 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }

    glTranslatef(0.06, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(956 - 443, 206);
    glVertex2f(956 - 425, 193);
    glVertex2f(956 - 436, 183);
    glEnd();
    abc[0] = { 956 - 425, 193 };
    abc[1] = { 956 - 414, 180 };
    abc[2] = { 956 - 436, 183 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld2, P);
        POld2 = P;
    }
}

void drawWordDecoration_right2(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.04, 0, 0);

    glLineWidth(1.5);
    // left2
    abc[0] = { 956 - 379, 106 };
    abc[1] = { 956 - 348, 105 };
    abc[2] = { 956 - 328, 125 };
    Point POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
}

void drawWordDecoration_right_leaves3(void) {
    glLoadIdentity();
    glTranslatef(0.04, 0, 0);

    glLineWidth(1.5);
    abc[0] = { 956 - 364, 107 };
    abc[1] = { 956 - 369, 118 };
    abc[2] = { 956 - 359, 121 };
    Point POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 956 - 359, 121 };
    abc[1] = { 956 - 350, 114 };
    abc[2] = { 956 - 364, 107 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glBegin(GL_LINES);
    glVertex2f(956 - 364, 107);
    glVertex2f(956 - 360, 117);
    glEnd();

    glTranslatef(0.03, 0.015, 0);
    abc[0] = { 956 - 364, 107 };
    abc[1] = { 956 - 369, 118 };
    abc[2] = { 956 - 359, 121 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 956 - 359, 121 };
    abc[1] = { 956 - 350, 114 };
    abc[2] = { 956 - 364, 107 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glBegin(GL_LINES);
    glVertex2f(956 - 364, 107);
    glVertex2f(956 - 360, 117);
    glEnd();

    glTranslatef(0.03, 0.02, 0);
    abc[0] = { 956 - 364, 107 };
    abc[1] = { 956 - 369, 118 };
    abc[2] = { 956 - 359, 121 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 956 - 359, 121 };
    abc[1] = { 956 - 350, 114 };
    abc[2] = { 956 - 364, 107 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glBegin(GL_LINES);
    glVertex2f(956 - 364, 107);
    glVertex2f(956 - 360, 117);
    glEnd();
}

void drawWordDecoration_right_leaves4(void) {
    glLoadIdentity();
    glTranslatef(0.04, 0, 0);

    glLineWidth(1.5);
    abc[0] = { 956 - 364, 107 };
    abc[1] = { 956 - 368, 98 };
    abc[2] = { 956 - 355, 95 };
    Point POld = abc[0];
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 956 - 355, 95 };
    abc[1] = { 956 - 352, 106 };
    abc[2] = { 956 - 364, 107 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glBegin(GL_LINES);
    glVertex2f(956 - 364, 107);
    glVertex2f(956 - 358, 100);
    glEnd();

    glTranslatef(0.035, 0.01, 0);
    abc[0] = { 956 - 364, 107 };
    abc[1] = { 956 - 368, 98 };
    abc[2] = { 956 - 355, 95 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 956 - 355, 95 };
    abc[1] = { 956 - 352, 106 };
    abc[2] = { 956 - 364, 107 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glBegin(GL_LINES);
    glVertex2f(956 - 364, 107);
    glVertex2f(956 - 358, 100);
    glEnd();

    glTranslatef(0.028, 0.022, 0);
    abc[0] = { 956 - 364, 107 };
    abc[1] = { 956 - 368, 98 };
    abc[2] = { 956 - 355, 95 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 956 - 355, 95 };
    abc[1] = { 956 - 352, 106 };
    abc[2] = { 956 - 364, 107 };
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glBegin(GL_LINES);
    glVertex2f(956 - 364, 107);
    glVertex2f(956 - 358, 100);
    glEnd();
}

void drawFuWord1(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glDisable(GL_DEPTH_TEST);

    glTranslatef(0.5, 0.25, 0);
    glPushMatrix();
    glRotatef(Fu_angle, 0, 0, 1);
    glTranslatef(1, 1, 0);

    // The background colour of Fu
    glColor3ub(255, 11, 13);
    glBegin(GL_POLYGON);
    glVertex2f(758 - 758, 538 - 453);
    glVertex2f(843 - 758, 453 - 453);
    glVertex2f(758 - 758, 368 - 453);
    glVertex2f(673 - 758, 453 - 453);
    glEnd();

    // The frame of Fu
    glColor3ub(237, 217, 160);
    glLineWidth(0.8);
    glBegin(GL_LINE_LOOP);
    glVertex2f(757 - 758, 533 - 453);
    glVertex2f(837 - 758, 453 - 453);
    glVertex2f(757 - 758, 373 - 453);
    glVertex2f(677 - 758, 453 - 453);
    glEnd();

    // The Fu word
    glColor3ub(0, 0, 0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(721 - 758, 485 - 453);
    glVertex2f(745 - 758, 485 - 453);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(715 - 758, 470 - 453);
    glVertex2f(751 - 758, 470 - 453);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(733 - 758, 470 - 453);
    glVertex2f(733 - 758, 415 - 453);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(721 - 758, 462 - 453);
    glVertex2f(721 - 758, 424 - 453);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(745 - 758, 462 - 453);
    glVertex2f(745 - 758, 433 - 453);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(758 - 758, 485 - 453);
    glVertex2f(795 - 758, 485 - 453);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(758 - 758, 485 - 453);
    glVertex2f(795 - 758, 485 - 453);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(776 - 758, 470 - 453);
    glVertex2f(781 - 758, 465 - 453);
    glVertex2f(776 - 758, 460 - 453);
    glVertex2f(771 - 758, 465 - 453);
    glEnd();

    glTranslatef(1.552, 1.162, 0);
    float R = 14;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n) - 758, R * sin(2 * PI * i / n) - 453);
    }
    glEnd();
    glTranslatef(0, 0.001, 0);
    glColor3ub(255, 11, 13);
    R = 9;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n) - 758, R * sin(2 * PI * i / n) - 453);
    }
    glEnd();
    glTranslatef(0, -0.085, 0);
    glColor3ub(0, 0, 0);
    R = 22;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n) - 758, R * sin(2 * PI * i / n) - 453);
    }
    glEnd();
    glTranslatef(0, 0, 0);
    glColor3ub(255, 11, 13);
    R = 17;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n) - 758, R * sin(2 * PI * i / n) - 453);
    }
    glEnd();

    glPopMatrix();
}

void drawFuWord2(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glDisable(GL_DEPTH_TEST);


    glTranslatef(0.5, 0.25, 0);
    glPushMatrix();
    glRotatef(Fu_angle, 0, 0, 1);
    glTranslatef(1, 1, 0);

    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(776 - 758, 470 - 453);
    glVertex2f(781 - 758, 465 - 453);
    glVertex2f(776 - 758, 460 - 453);
    glVertex2f(771 - 758, 465 - 453);
    glEnd();
    glLineWidth(3.5);
    glBegin(GL_LINES);
    glVertex2f(765.5 - 758, 432 - 453);
    glVertex2f(787.5 - 758, 432 - 453);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(776.5 - 758, 442 - 453);
    glVertex2f(776.5 - 758, 422 - 453);
    glEnd();
}

void drawCandle1(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    glLoadIdentity();
    glLineWidth(8);
    glColor3ub(93, 62, 11);
    glBegin(GL_LINES);
    glVertex2f(211, 157);
    glVertex2f(211, 147);
    glEnd();
    glTranslatef(0.422, 0.4, 0);
    float R = 4.5;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();

    glLoadIdentity();
    glColor3ub(231, 102, 56);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(194, 147);
    glVertex2f(228, 147);
    glEnd();
    glTranslatef(0.39, 0.368, 0);
    R = 5.2;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.07, 0, 0);
    R = 5.2;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();

    glLoadIdentity();
    glColor3ub(221, 56, 19);
    glBegin(GL_POLYGON);
    glVertex2f(194, 143);
    glVertex2f(231, 143);
    glVertex2f(231, 103);
    glVertex2f(194, 103);
    glEnd();

    glLoadIdentity();
    glTranslatef(0, -0.12, 0);
    glColor3ub(231, 102, 56);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(194, 147);
    glVertex2f(228, 147);
    glEnd();
    glTranslatef(0.39, 0.368, 0);
    R = 5.2;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.07, 0, 0);
    R = 5.2;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();

    glLoadIdentity();
    glColor3ub(230, 104, 65);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2f(204, 146);
    glVertex2f(204, 126);
    glEnd();
    glTranslatef(0.408, 0.31, 0);
    R = 4;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawCandle2(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    glTranslatef(1.13, 0, 0);
    glLineWidth(8);
    glColor3ub(93, 62, 11);
    glBegin(GL_LINES);
    glVertex2f(211, 157);
    glVertex2f(211, 147);
    glEnd();
    glTranslatef(0.422, 0.4, 0);
    float R = 4.5;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();

    glLoadIdentity();
    glTranslatef(1.13, 0, 0);
    glColor3ub(231, 102, 56);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(194, 147);
    glVertex2f(228, 147);
    glEnd();
    glTranslatef(0.39, 0.368, 0);
    R = 5.2;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.07, 0, 0);
    R = 5.2;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();

    glLoadIdentity();
    glTranslatef(1.13, 0, 0);
    glColor3ub(221, 56, 19);
    glBegin(GL_POLYGON);
    glVertex2f(194, 143);
    glVertex2f(231, 143);
    glVertex2f(231, 103);
    glVertex2f(194, 103);
    glEnd();

    glLoadIdentity();
    glTranslatef(1.13, 0, 0);
    glTranslatef(0, -0.12, 0);
    glColor3ub(231, 102, 56);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(194, 147);
    glVertex2f(228, 147);
    glEnd();
    glTranslatef(0.39, 0.368, 0);
    R = 5.2;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(0.07, 0, 0);
    R = 5.2;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();

    glLoadIdentity();
    glTranslatef(1.13, 0, 0);
    glColor3ub(230, 104, 65);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2f(204, 146);
    glVertex2f(204, 126);
    glEnd();
    glTranslatef(0.408, 0.31, 0);
    R = 4;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawMatch(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    glTranslatef(1.3, 0, 0);

    // The fire part
    // Part1
    glColor3ub(244, 110, 11);
    glBegin(GL_POLYGON);
    glVertex2f(213 + match_x, 160); glVertex2f(205 + match_x, 163); glVertex2f(201 + match_x, 169); glVertex2f(197 + match_x, 181);
    glVertex2f(199 + match_x, 190); glVertex2f(201 + match_x, 194); glVertex2f(204 + match_x, 199); glVertex2f(203 + match_x, 201);
    glVertex2f(202 + match_x, 202); glVertex2f(201 + match_x, 203); glVertex2f(196 + match_x, 204); glVertex2f(208 + match_x, 199);
    glVertex2f(210 + match_x, 198); glVertex2f(212 + match_x, 201); glVertex2f(208 + match_x, 211); glVertex2f(209 + match_x, 214);
    glVertex2f(210 + match_x, 218); glVertex2f(213 + match_x, 223); glVertex2f(217 + match_x, 218); glVertex2f(218 + match_x, 214);
    glVertex2f(220 + match_x, 207); glVertex2f(221 + match_x, 201); glVertex2f(224 + match_x, 197); glVertex2f(227 + match_x, 198);
    glVertex2f(229 + match_x, 204); glVertex2f(226 + match_x, 208); glVertex2f(228 + match_x, 210); glVertex2f(230 + match_x, 213);
    glVertex2f(232 + match_x, 206); glVertex2f(235 + match_x, 195); glVertex2f(236 + match_x, 190); glVertex2f(235 + match_x, 188);
    glVertex2f(235 + match_x, 182); glVertex2f(234 + match_x, 176); glVertex2f(231 + match_x, 171); glVertex2f(230 + match_x, 167);
    glVertex2f(225 + match_x, 162);
    glEnd();
    // Part2
    glTranslatef(0.434, 0.44, 0);
    glColor3ub(254, 226, 21);
    float R1 = 10, R2 = 16;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R1 * cos(2 * PI * i / n) + match_x, R2 * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-0.005, 0.06, 0);
    R1 = 4, R2 = 6;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R1 * cos(2 * PI * i / n) + match_x, R2 * sin(2 * PI * i / n));
    }
    glEnd();

    // The stick part
    glLoadIdentity();
    glColor3ub(231, 178, 80);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(870 + match_x, 161);
    glVertex2f(898 + match_x, 119);
    glEnd();
    glColor3ub(203, 41, 45);
    glTranslatef(1.737, 0.41, 0);
    float R = 4.5;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * PI * i / n) + match_x, R * sin(2 * PI * i / n));
    }
    glEnd();
}

void drawFire1(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    glTranslatef(1.12, 0, 0);

    // The fire part
    // Part1
    glColor3ub(244, 110, 11);
    glBegin(GL_POLYGON);
    glVertex3f(213, 160, fire_depth); glVertex3f(205, 163, fire_depth); glVertex3f(201, 169, fire_depth); glVertex3f(197, 181, fire_depth);
    glVertex3f(199, 190, fire_depth); glVertex3f(201, 194, fire_depth); glVertex3f(204, 199, fire_depth); glVertex3f(203, 201, fire_depth);
    glVertex3f(202, 202, fire_depth); glVertex3f(201, 203, fire_depth); glVertex3f(196, 204, fire_depth); glVertex3f(208, 199, fire_depth);
    glVertex3f(210, 198, fire_depth); glVertex3f(212, 201, fire_depth); glVertex3f(208, 211, fire_depth); glVertex3f(209, 214, fire_depth);
    glVertex3f(210, 218, fire_depth); glVertex3f(213, 223, fire_depth); glVertex3f(217, 218, fire_depth); glVertex3f(218, 214, fire_depth);
    glVertex3f(220, 207, fire_depth); glVertex3f(221, 201, fire_depth); glVertex3f(224, 197, fire_depth); glVertex3f(227, 198, fire_depth);
    glVertex3f(229, 204, fire_depth); glVertex3f(226, 208, fire_depth); glVertex3f(228, 210, fire_depth); glVertex3f(230, 213, fire_depth);
    glVertex3f(232, 206, fire_depth); glVertex3f(235, 195, fire_depth); glVertex3f(236, 190, fire_depth); glVertex3f(235, 188, fire_depth);
    glVertex3f(235, 182, fire_depth); glVertex3f(234, 176, fire_depth); glVertex3f(231, 171, fire_depth); glVertex3f(230, 167, fire_depth);
    glVertex3f(225, 162, fire_depth);
    glEnd();
    // Part2
    glTranslatef(0.434, 0.44, 0);
    glColor3ub(254, 226, 21);
    float R1 = 10, R2 = 16;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex3f(R1 * cos(2 * PI * i / n), R2 * sin(2 * PI * i / n), fire_depth);
    }
    glEnd();
    glTranslatef(-0.005, 0.06, 0);
    R1 = 4, R2 = 6;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex3f(R1 * cos(2 * PI * i / n), R2 * sin(2 * PI * i / n), fire_depth);
    }
    glEnd();
}

void drawFire2(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    glTranslatef(-0.01, 0, 0);

    // The fire part
    // Part1
    glColor3ub(244, 110, 11);
    glBegin(GL_POLYGON);
    glVertex3f(213, 160, fire_depth2); glVertex3f(205, 163, fire_depth2); glVertex3f(201, 169, fire_depth2); glVertex3f(197, 181, fire_depth2);
    glVertex3f(199, 190, fire_depth2); glVertex3f(201, 194, fire_depth2); glVertex3f(204, 199, fire_depth2); glVertex3f(203, 201, fire_depth2);
    glVertex3f(202, 202, fire_depth2); glVertex3f(201, 203, fire_depth2); glVertex3f(196, 204, fire_depth2); glVertex3f(208, 199, fire_depth2);
    glVertex3f(210, 198, fire_depth2); glVertex3f(212, 201, fire_depth2); glVertex3f(208, 211, fire_depth2); glVertex3f(209, 214, fire_depth2);
    glVertex3f(210, 218, fire_depth2); glVertex3f(213, 223, fire_depth2); glVertex3f(217, 218, fire_depth2); glVertex3f(218, 214, fire_depth2);
    glVertex3f(220, 207, fire_depth2); glVertex3f(221, 201, fire_depth2); glVertex3f(224, 197, fire_depth2); glVertex3f(227, 198, fire_depth2);
    glVertex3f(229, 204, fire_depth2); glVertex3f(226, 208, fire_depth2); glVertex3f(228, 210, fire_depth2); glVertex3f(230, 213, fire_depth2);
    glVertex3f(232, 206, fire_depth2); glVertex3f(235, 195, fire_depth2); glVertex3f(236, 190, fire_depth2); glVertex3f(235, 188, fire_depth2);
    glVertex3f(235, 182, fire_depth2); glVertex3f(234, 176, fire_depth2); glVertex3f(231, 171, fire_depth2); glVertex3f(230, 167, fire_depth2);
    glVertex3f(225, 162, fire_depth2);
    glEnd();
    // Part2
    glTranslatef(0.434, 0.44, 0);
    glColor3ub(254, 226, 21);
    float R1 = 10, R2 = 16;
    float n = 80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex3f(R1 * cos(2 * PI * i / n), R2 * sin(2 * PI * i / n), fire_depth2);
    }
    glEnd();
    glTranslatef(-0.005, 0.06, 0);
    R1 = 4, R2 = 6;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex3f(R1 * cos(2 * PI * i / n), R2 * sin(2 * PI * i / n), fire_depth2);
    }
    glEnd();
}

void drawenvelopee(void) {
    glLoadIdentity();

    // Enable anti-aliasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2f(0 + white_background_x, 800);
    glVertex2f(1000 + white_background_x, 800);
    glVertex2f(1000 + white_background_x, 0);
    glVertex2f(0 + white_background_x, 0);
    glEnd();

    glRotatef(envelope_angle, 0, 0, 1);
    glScalef(envelope_x_scale, envelope_y_scale, 0);

    glColor3ub(181, 41, 52);
    glBegin(GL_POLYGON);
    glVertex3f(115 + envelope_letter_x1, 680, 0);
    glVertex3f(885 + envelope_letter_x1, 680, 0);
    glVertex3f(885 + envelope_letter_x1, 120, 0);
    glVertex3f(115 + envelope_letter_x1, 120, 0);
    glEnd();

    // Left half of the envelopee
    glColor3ub(217, 217, 217);
    glBegin(GL_POLYGON);
    glVertex3f(95 + envelope_left_part_x, 705, 0); glVertex3f(800 + envelope_left_part_x, 705, 0); glVertex3f(750 + envelope_left_part_x, 644, 0);
    glVertex3f(800 + envelope_left_part_x, 583, 0); glVertex3f(750 + envelope_left_part_x, 522, 0); glVertex3f(800 + envelope_left_part_x, 461, 0);
    glVertex3f(750 + envelope_left_part_x, 400, 0); glVertex3f(800 + envelope_left_part_x, 339, 0); glVertex3f(750 + envelope_left_part_x, 278, 0);
    glVertex3f(800 + envelope_left_part_x, 217, 0); glVertex3f(750 + envelope_left_part_x, 156, 0); glVertex3f(800 + envelope_left_part_x, 95, 0);
    glVertex3f(95 + envelope_left_part_x, 95, 0);
    glEnd();

    glColor3ub(217, 217, 217);
    // Right half of the envelopee
    glBegin(GL_POLYGON);
    glVertex3f(905 + envelope_right_part_x, 705, 0); glVertex3f(800 + envelope_right_part_x, 705, 0); glVertex3f(750 + envelope_right_part_x, 644, 0);
    glVertex3f(800 + envelope_right_part_x, 583, 0); glVertex3f(750 + envelope_right_part_x, 522, 0); glVertex3f(800 + envelope_right_part_x, 461, 0);
    glVertex3f(750 + envelope_right_part_x, 400, 0); glVertex3f(800 + envelope_right_part_x, 339, 0); glVertex3f(750 + envelope_right_part_x, 278, 0);
    glVertex3f(800 + envelope_right_part_x, 217, 0); glVertex3f(750 + envelope_right_part_x, 156, 0); glVertex3f(800 + envelope_right_part_x, 95, 0);
    glVertex3f(905 + envelope_right_part_x, 95, 0);
    glEnd();

    // Top half of the envelopee frame
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(120 + envelope_left_part_x, 705, 0);
    glVertex3f(155 + envelope_left_part_x, 705, 0);
    glVertex3f(162 + envelope_left_part_x, 685, 0);
    glVertex3f(127 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(172 + envelope_left_part_x, 705, 0);
    glVertex3f(207 + envelope_left_part_x, 705, 0);
    glVertex3f(214 + envelope_left_part_x, 685, 0);
    glVertex3f(179 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(222 + envelope_left_part_x, 705, 0);
    glVertex3f(257 + envelope_left_part_x, 705, 0);
    glVertex3f(264 + envelope_left_part_x, 685, 0);
    glVertex3f(229 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(272 + envelope_left_part_x, 705, 0);
    glVertex3f(307 + envelope_left_part_x, 705, 0);
    glVertex3f(314 + envelope_left_part_x, 685, 0);
    glVertex3f(279 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(322 + envelope_left_part_x, 705, 0);
    glVertex3f(357 + envelope_left_part_x, 705, 0);
    glVertex3f(364 + envelope_left_part_x, 685, 0);
    glVertex3f(329 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(372 + envelope_left_part_x, 705, 0);
    glVertex3f(407 + envelope_left_part_x, 705, 0);
    glVertex3f(414 + envelope_left_part_x, 685, 0);
    glVertex3f(379 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(422 + envelope_left_part_x, 705, 0);
    glVertex3f(457 + envelope_left_part_x, 705, 0);
    glVertex3f(464 + envelope_left_part_x, 685, 0);
    glVertex3f(429 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(472 + envelope_left_part_x, 705, 0);
    glVertex3f(507 + envelope_left_part_x, 705, 0);
    glVertex3f(514 + envelope_left_part_x, 685, 0);
    glVertex3f(479 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(522 + envelope_left_part_x, 705, 0);
    glVertex3f(557 + envelope_left_part_x, 705, 0);
    glVertex3f(564 + envelope_left_part_x, 685, 0);
    glVertex3f(529 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(572 + envelope_left_part_x, 705, 0);
    glVertex3f(607 + envelope_left_part_x, 705, 0);
    glVertex3f(614 + envelope_left_part_x, 685, 0);
    glVertex3f(579 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(622 + envelope_left_part_x, 705, 0);
    glVertex3f(657 + envelope_left_part_x, 705, 0);
    glVertex3f(664 + envelope_left_part_x, 685, 0);
    glVertex3f(629 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(672 + envelope_left_part_x, 705, 0);
    glVertex3f(707 + envelope_left_part_x, 705, 0);
    glVertex3f(714 + envelope_left_part_x, 685, 0);
    glVertex3f(679 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(722 + envelope_left_part_x, 705, 0);
    glVertex3f(757 + envelope_left_part_x, 705, 0);
    glVertex3f(764 + envelope_left_part_x, 685, 0);
    glVertex3f(729 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(772 + envelope_left_part_x, 705, 0);
    glVertex3f(800 + envelope_left_part_x, 705, 0);
    glVertex3f(783 + envelope_left_part_x, 685, 0);
    glVertex3f(779 + envelope_left_part_x, 685, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(800 + envelope_right_part_x, 705, 0);
    glVertex3f(807 + envelope_right_part_x, 705, 0);
    glVertex3f(814 + envelope_right_part_x, 685, 0);
    glVertex3f(783 + envelope_right_part_x, 685, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(822 + envelope_right_part_x, 705, 0);
    glVertex3f(857 + envelope_right_part_x, 705, 0);
    glVertex3f(864 + envelope_right_part_x, 685, 0);
    glVertex3f(829 + envelope_right_part_x, 685, 0);
    glEnd();
    // Bottom half of the envelopee frame
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(120 + envelope_left_part_x, 115, 0);
    glVertex3f(155 + envelope_left_part_x, 115, 0);
    glVertex3f(162 + envelope_left_part_x, 95, 0);
    glVertex3f(127 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(172 + envelope_left_part_x, 115, 0);
    glVertex3f(207 + envelope_left_part_x, 115, 0);
    glVertex3f(214 + envelope_left_part_x, 95, 0);
    glVertex3f(179 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(222 + envelope_left_part_x, 115, 0);
    glVertex3f(257 + envelope_left_part_x, 115, 0);
    glVertex3f(264 + envelope_left_part_x, 95, 0);
    glVertex3f(229 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(272 + envelope_left_part_x, 115, 0);
    glVertex3f(307 + envelope_left_part_x, 115, 0);
    glVertex3f(314 + envelope_left_part_x, 95, 0);
    glVertex3f(279 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(322 + envelope_left_part_x, 115, 0);
    glVertex3f(357 + envelope_left_part_x, 115, 0);
    glVertex3f(364 + envelope_left_part_x, 95, 0);
    glVertex3f(329 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(372 + envelope_left_part_x, 115, 0);
    glVertex3f(407 + envelope_left_part_x, 115, 0);
    glVertex3f(414 + envelope_left_part_x, 95, 0);
    glVertex3f(379 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(422 + envelope_left_part_x, 115, 0);
    glVertex3f(457 + envelope_left_part_x, 115, 0);
    glVertex3f(464 + envelope_left_part_x, 95, 0);
    glVertex3f(429 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(472 + envelope_left_part_x, 115, 0);
    glVertex3f(507 + envelope_left_part_x, 115, 0);
    glVertex3f(514 + envelope_left_part_x, 95, 0);
    glVertex3f(479 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(522 + envelope_left_part_x, 115, 0);
    glVertex3f(557 + envelope_left_part_x, 115, 0);
    glVertex3f(564 + envelope_left_part_x, 95, 0);
    glVertex3f(529 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(572 + envelope_left_part_x, 115, 0);
    glVertex3f(607 + envelope_left_part_x, 115, 0);
    glVertex3f(614 + envelope_left_part_x, 95, 0);
    glVertex3f(579 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(622 + envelope_left_part_x, 115, 0);
    glVertex3f(657 + envelope_left_part_x, 115, 0);
    glVertex3f(664 + envelope_left_part_x, 95, 0);
    glVertex3f(629 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(672 + envelope_left_part_x, 115, 0);
    glVertex3f(707 + envelope_left_part_x, 115, 0);
    glVertex3f(714 + envelope_left_part_x, 95, 0);
    glVertex3f(679 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(722 + envelope_left_part_x, 115, 0);
    glVertex3f(757 + envelope_left_part_x, 115, 0);
    glVertex3f(764 + envelope_left_part_x, 95, 0);
    glVertex3f(729 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(772 + envelope_left_part_x, 115, 0);
    glVertex3f(784 + envelope_left_part_x, 115, 0);
    glVertex3f(800 + envelope_left_part_x, 95, 0);
    glVertex3f(779 + envelope_left_part_x, 95, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(784 + envelope_right_part_x, 115, 0);
    glVertex3f(807 + envelope_right_part_x, 115, 0);
    glVertex3f(814 + envelope_right_part_x, 95, 0);
    glVertex3f(800 + envelope_right_part_x, 95, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(822 + envelope_right_part_x, 115, 0);
    glVertex3f(857 + envelope_right_part_x, 115, 0);
    glVertex3f(864 + envelope_right_part_x, 95, 0);
    glVertex3f(829 + envelope_right_part_x, 95, 0);
    glEnd();
    // Left half of the envelopee frame
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(95 + envelope_left_part_x, 673, 0);
    glVertex3f(115 + envelope_left_part_x, 666, 0);
    glVertex3f(115 + envelope_left_part_x, 631, 0);
    glVertex3f(95 + envelope_left_part_x, 638, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(95 + envelope_left_part_x, 623, 0);
    glVertex3f(115 + envelope_left_part_x, 616, 0);
    glVertex3f(115 + envelope_left_part_x, 581, 0);
    glVertex3f(95 + envelope_left_part_x, 588, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(95 + envelope_left_part_x, 573, 0);
    glVertex3f(115 + envelope_left_part_x, 566, 0);
    glVertex3f(115 + envelope_left_part_x, 531, 0);
    glVertex3f(95 + envelope_left_part_x, 538, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(95 + envelope_left_part_x, 523, 0);
    glVertex3f(115 + envelope_left_part_x, 516, 0);
    glVertex3f(115 + envelope_left_part_x, 481, 0);
    glVertex3f(95 + envelope_left_part_x, 488, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(95 + envelope_left_part_x, 473, 0);
    glVertex3f(115 + envelope_left_part_x, 466, 0);
    glVertex3f(115 + envelope_left_part_x, 431, 0);
    glVertex3f(95 + envelope_left_part_x, 438, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(95 + envelope_left_part_x, 423, 0);
    glVertex3f(115 + envelope_left_part_x, 416, 0);
    glVertex3f(115 + envelope_left_part_x, 381, 0);
    glVertex3f(95 + envelope_left_part_x, 388, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(95 + envelope_left_part_x, 373, 0);
    glVertex3f(115 + envelope_left_part_x, 366, 0);
    glVertex3f(115 + envelope_left_part_x, 331, 0);
    glVertex3f(95 + envelope_left_part_x, 338, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(95 + envelope_left_part_x, 323, 0);
    glVertex3f(115 + envelope_left_part_x, 316, 0);
    glVertex3f(115 + envelope_left_part_x, 281, 0);
    glVertex3f(95 + envelope_left_part_x, 288, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(95 + envelope_left_part_x, 273, 0);
    glVertex3f(115 + envelope_left_part_x, 266, 0);
    glVertex3f(115 + envelope_left_part_x, 231, 0);
    glVertex3f(95 + envelope_left_part_x, 238, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(95 + envelope_left_part_x, 223, 0);
    glVertex3f(115 + envelope_left_part_x, 216, 0);
    glVertex3f(115 + envelope_left_part_x, 181, 0);
    glVertex3f(95 + envelope_left_part_x, 188, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(95 + envelope_left_part_x, 173, 0);
    glVertex3f(115 + envelope_left_part_x, 166, 0);
    glVertex3f(115 + envelope_left_part_x, 131, 0);
    glVertex3f(95 + envelope_left_part_x, 138, 0);
    glEnd();
    // Right half of the envelopee frame
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(885 + envelope_right_part_x, 673, 0);
    glVertex3f(905 + envelope_right_part_x, 666, 0);
    glVertex3f(905 + envelope_right_part_x, 631, 0);
    glVertex3f(885 + envelope_right_part_x, 638, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(885 + envelope_right_part_x, 623, 0);
    glVertex3f(905 + envelope_right_part_x, 616, 0);
    glVertex3f(905 + envelope_right_part_x, 581, 0);
    glVertex3f(885 + envelope_right_part_x, 588, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(885 + envelope_right_part_x, 573, 0);
    glVertex3f(905 + envelope_right_part_x, 566, 0);
    glVertex3f(905 + envelope_right_part_x, 531, 0);
    glVertex3f(885 + envelope_right_part_x, 538, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(885 + envelope_right_part_x, 523, 0);
    glVertex3f(905 + envelope_right_part_x, 516, 0);
    glVertex3f(905 + envelope_right_part_x, 481, 0);
    glVertex3f(885 + envelope_right_part_x, 488, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(885 + envelope_right_part_x, 473, 0);
    glVertex3f(905 + envelope_right_part_x, 466, 0);
    glVertex3f(905 + envelope_right_part_x, 431, 0);
    glVertex3f(885 + envelope_right_part_x, 438, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(885 + envelope_right_part_x, 423, 0);
    glVertex3f(905 + envelope_right_part_x, 416, 0);
    glVertex3f(905 + envelope_right_part_x, 381, 0);
    glVertex3f(885 + envelope_right_part_x, 388, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(885 + envelope_right_part_x, 373, 0);
    glVertex3f(905 + envelope_right_part_x, 366, 0);
    glVertex3f(905 + envelope_right_part_x, 331, 0);
    glVertex3f(885 + envelope_right_part_x, 338, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(885 + envelope_right_part_x, 323, 0);
    glVertex3f(905 + envelope_right_part_x, 316, 0);
    glVertex3f(905 + envelope_right_part_x, 281, 0);
    glVertex3f(885 + envelope_right_part_x, 288, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(885 + envelope_right_part_x, 273, 0);
    glVertex3f(905 + envelope_right_part_x, 266, 0);
    glVertex3f(905 + envelope_right_part_x, 231, 0);
    glVertex3f(885 + envelope_right_part_x, 238, 0);
    glEnd();
    glColor3ub(207, 75, 73);
    glBegin(GL_POLYGON);
    glVertex3f(885 + envelope_right_part_x, 223, 0);
    glVertex3f(905 + envelope_right_part_x, 216, 0);
    glVertex3f(905 + envelope_right_part_x, 181, 0);
    glVertex3f(885 + envelope_right_part_x, 188, 0);
    glEnd();
    glColor3ub(53, 117, 178);
    glBegin(GL_POLYGON);
    glVertex3f(885 + envelope_right_part_x, 173, 0);
    glVertex3f(905 + envelope_right_part_x, 166, 0);
    glVertex3f(905 + envelope_right_part_x, 131, 0);
    glVertex3f(885 + envelope_right_part_x, 138, 0);
    glEnd();

    // Boxs in the top left corner of the envelopee
    glLineWidth(1);
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(140 + envelope_left_part_x, 664, 0);
    glVertex3f(170 + envelope_left_part_x, 664, 0);
    glVertex3f(170 + envelope_left_part_x, 634, 0);
    glVertex3f(140 + envelope_left_part_x, 634, 0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(180 + envelope_left_part_x, 664, 0);
    glVertex3f(210 + envelope_left_part_x, 664, 0);
    glVertex3f(210 + envelope_left_part_x, 634, 0);
    glVertex3f(180 + envelope_left_part_x, 634, 0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(220 + envelope_left_part_x, 664, 0);
    glVertex3f(250 + envelope_left_part_x, 664, 0);
    glVertex3f(250 + envelope_left_part_x, 634, 0);
    glVertex3f(220 + envelope_left_part_x, 634, 0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(260 + envelope_left_part_x, 664, 0);
    glVertex3f(290 + envelope_left_part_x, 664, 0);
    glVertex3f(290 + envelope_left_part_x, 634, 0);
    glVertex3f(260 + envelope_left_part_x, 634, 0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(300 + envelope_left_part_x, 664, 0);
    glVertex3f(330 + envelope_left_part_x, 664, 0);
    glVertex3f(330 + envelope_left_part_x, 634, 0);
    glVertex3f(300 + envelope_left_part_x, 634, 0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(340 + envelope_left_part_x, 664, 0);
    glVertex3f(370 + envelope_left_part_x, 664, 0);
    glVertex3f(370 + envelope_left_part_x, 634, 0);
    glVertex3f(340 + envelope_left_part_x, 634, 0);
    glEnd();

    // Draw the postcode on the envelope
    setFont(35, ANSI_CHARSET, "Brush Script MT");
    glRasterPos2f(148 + envelope_left_part_x, 639);
    drawString(" 2");
    glRasterPos2f(183 + envelope_left_part_x, 639);
    drawString(" 1");
    glRasterPos2f(222 + envelope_left_part_x, 639);
    drawString(" 5");
    glRasterPos2f(262 + envelope_left_part_x, 639);
    drawString(" 0");
    glRasterPos2f(302 + envelope_left_part_x, 639);
    drawString(" 0");
    glRasterPos2f(342 + envelope_left_part_x, 639);
    drawString(" 0");

    // Draw the window on the envelope
    // The left part of the window
    glLineWidth(1);
    abc[0] = { 636 + envelope_left_part_x, 340 };
    abc[1] = { 655 + envelope_left_part_x, 372 };
    abc[2] = { 703 + envelope_left_part_x, 376 };
    Point POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 703 + envelope_left_part_x, 376 };
    abc[1] = { 754 + envelope_left_part_x, 379 };
    abc[2] = { 775 + envelope_left_part_x, 358 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 637 + envelope_left_part_x, 332 };
    abc[1] = { 660 + envelope_left_part_x, 364 };
    abc[2] = { 680 + envelope_left_part_x, 366 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 680 + envelope_left_part_x, 366 };
    abc[1] = { 701 + envelope_left_part_x, 373 };
    abc[2] = { 722 + envelope_left_part_x, 368 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 722 + envelope_left_part_x, 368 };
    abc[1] = { 747 + envelope_left_part_x, 365 };
    abc[2] = { 767 + envelope_left_part_x, 344 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 722 + envelope_left_part_x, 368 };
    abc[1] = { 747 + envelope_left_part_x, 365 };
    abc[2] = { 767 + envelope_left_part_x, 344 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 637 + envelope_left_part_x, 332 };
    abc[1] = { 637 + envelope_left_part_x, 322 };
    abc[2] = { 638 + envelope_left_part_x, 254 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    abc[0] = { 637 + envelope_left_part_x, 332 };
    abc[1] = { 629 + envelope_left_part_x, 352 };
    abc[2] = { 595 + envelope_left_part_x, 341 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 595 + envelope_left_part_x, 341 };
    abc[1] = { 600 + envelope_left_part_x, 305 };
    abc[2] = { 601 + envelope_left_part_x, 250 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 601 + envelope_left_part_x, 343 };
    abc[1] = { 606 + envelope_left_part_x, 306 };
    abc[2] = { 606 + envelope_left_part_x, 250 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 601 + envelope_left_part_x, 250 };
    abc[1] = { 619 + envelope_left_part_x, 244 };
    abc[2] = { 638 + envelope_left_part_x, 254 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 628 + envelope_left_part_x, 328 };
    abc[1] = { 625 + envelope_left_part_x, 339 };
    abc[2] = { 609 + envelope_left_part_x, 337 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 609 + envelope_left_part_x, 337 };
    abc[1] = { 613 + envelope_left_part_x, 303 };
    abc[2] = { 613 + envelope_left_part_x, 257 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 613 + envelope_left_part_x, 257 };
    abc[1] = { 622 + envelope_left_part_x, 255 };
    abc[2] = { 628 + envelope_left_part_x, 261 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 628 + envelope_left_part_x, 261 };
    abc[1] = { 628 + envelope_left_part_x, 298 };
    abc[2] = { 628 + envelope_left_part_x, 328 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 637 + envelope_left_part_x, 254 };
    abc[1] = { 699 + envelope_left_part_x, 259 };
    abc[2] = { 762 + envelope_left_part_x, 262 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 630 + envelope_left_part_x, 250 };
    abc[1] = { 707 + envelope_left_part_x, 241 };
    abc[2] = { 770 + envelope_left_part_x, 253 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 767 + envelope_left_part_x, 344 };
    abc[1] = { 765 + envelope_left_part_x, 335 };
    abc[2] = { 763 + envelope_left_part_x, 316 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 638 + envelope_left_part_x, 272 };
    abc[1] = { 690 + envelope_left_part_x, 278 };
    abc[2] = { 751 + envelope_left_part_x, 277 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 751 + envelope_left_part_x, 277 };
    abc[1] = { 754 + envelope_left_part_x, 319 };
    abc[2] = { 742 + envelope_left_part_x, 362 };
    POld = abc[0];
    glLineWidth(2);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(610 + envelope_left_part_x, 327);
    glVertex2f(628 + envelope_left_part_x, 327);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(610 + envelope_left_part_x, 318);
    glVertex2f(626 + envelope_left_part_x, 319);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(611 + envelope_left_part_x, 298);
    glVertex2f(628 + envelope_left_part_x, 300);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(612 + envelope_left_part_x, 291);
    glVertex2f(627 + envelope_left_part_x, 291);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(613 + envelope_left_part_x, 271);
    glVertex2f(626 + envelope_left_part_x, 271);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(613 + envelope_left_part_x, 263);
    glVertex2f(627 + envelope_left_part_x, 264);
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(751 + envelope_left_part_x, 277);
    glVertex2f(762 + envelope_left_part_x, 263);
    glEnd();
    // cloud1
    abc[0] = { 636 + envelope_left_part_x, 305 };
    abc[1] = { 648 + envelope_left_part_x, 315 };
    abc[2] = { 655 + envelope_left_part_x, 306 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 655 + envelope_left_part_x, 306 };
    abc[1] = { 664 + envelope_left_part_x, 317 };
    abc[2] = { 673 + envelope_left_part_x, 306 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 673 + envelope_left_part_x, 306 };
    abc[1] = { 682 + envelope_left_part_x, 307 };
    abc[2] = { 683 + envelope_left_part_x, 298 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 683 + envelope_left_part_x, 298 };
    abc[1] = { 682 + envelope_left_part_x, 292 };
    abc[2] = { 673 + envelope_left_part_x, 291 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 673 + envelope_left_part_x, 291 };
    abc[1] = { 665 + envelope_left_part_x, 280 };
    abc[2] = { 655 + envelope_left_part_x, 290 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 655 + envelope_left_part_x, 290 };
    abc[1] = { 645 + envelope_left_part_x, 282 };
    abc[2] = { 638 + envelope_left_part_x, 288 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    // cloud2
    abc[0] = { 711 + envelope_left_part_x, 343 };
    abc[1] = { 700 + envelope_left_part_x, 355 };
    abc[2] = { 721 + envelope_left_part_x, 350 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 721 + envelope_left_part_x, 350 };
    abc[1] = { 729 + envelope_left_part_x, 362 };
    abc[2] = { 735 + envelope_left_part_x, 349 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 735 + envelope_left_part_x, 349 };
    abc[1] = { 737 + envelope_left_part_x, 351 };
    abc[2] = { 744 + envelope_left_part_x, 351 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 746 + envelope_left_part_x, 342 };
    abc[1] = { 740 + envelope_left_part_x, 337 };
    abc[2] = { 736 + envelope_left_part_x, 339 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 736 + envelope_left_part_x, 339 };
    abc[1] = { 727 + envelope_left_part_x, 326 };
    abc[2] = { 719 + envelope_left_part_x, 337 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 719 + envelope_left_part_x, 337 };
    abc[1] = { 707 + envelope_left_part_x, 330 };
    abc[2] = { 711 + envelope_left_part_x, 343 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 766 + envelope_left_part_x, 344 };
    abc[1] = { 769 + envelope_left_part_x, 353 };
    abc[2] = { 780 + envelope_left_part_x, 361 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }

    // The right part of the window
    abc[0] = { 780 + envelope_right_part_x, 361 };
    abc[1] = { 790 + envelope_right_part_x, 369 };
    abc[2] = { 799 + envelope_right_part_x, 366 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 799 + envelope_right_part_x, 366 };
    abc[1] = { 797 + envelope_right_part_x, 317 };
    abc[2] = { 801 + envelope_right_part_x, 255 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 801 + envelope_right_part_x, 255 };
    abc[1] = { 780 + envelope_right_part_x, 256 };
    abc[2] = { 762 + envelope_right_part_x, 262 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 763 + envelope_right_part_x, 316 };
    abc[1] = { 762 + envelope_right_part_x, 287 };
    abc[2] = { 763 + envelope_right_part_x, 264 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 790 + envelope_right_part_x, 358 };
    abc[1] = { 781 + envelope_right_part_x, 355 };
    abc[2] = { 773 + envelope_right_part_x, 336 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 773 + envelope_right_part_x, 336 };
    abc[1] = { 771 + envelope_right_part_x, 303 };
    abc[2] = { 772 + envelope_right_part_x, 269 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 772 + envelope_right_part_x, 269 };
    abc[1] = { 782 + envelope_right_part_x, 267 };
    abc[2] = { 790 + envelope_right_part_x, 267 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 790 + envelope_right_part_x, 267 };
    abc[1] = { 788 + envelope_right_part_x, 312 };
    abc[2] = { 789 + envelope_right_part_x, 358 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    abc[0] = { 770 + envelope_right_part_x, 254 };
    abc[1] = { 775 + envelope_right_part_x, 255 };
    abc[2] = { 782 + envelope_right_part_x, 256 };
    POld = abc[0];
    glLineWidth(1);
    for (double t = 0.0; t <= 1.0; t += 0.1) {
        Point P = drawBezier(abc[0], abc[1], abc[2], t);
        drawLine(POld, P);
        POld = P;
    }
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(776 + envelope_right_part_x, 343);
    glVertex2f(788 + envelope_right_part_x, 343);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(773 + envelope_right_part_x, 336);
    glVertex2f(788 + envelope_right_part_x, 336);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(772 + envelope_right_part_x, 318);
    glVertex2f(788 + envelope_right_part_x, 317);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(771 + envelope_right_part_x, 309);
    glVertex2f(788 + envelope_right_part_x, 307);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(772 + envelope_right_part_x, 287);
    glVertex2f(788 + envelope_right_part_x, 289);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(772 + envelope_right_part_x, 280);
    glVertex2f(788 + envelope_right_part_x, 280);
    glEnd();

    // The stamp on the top right of the envelope
    // The left part of stamp
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(776 + envelope_left_part_x, 675);
    glVertex2f(716 + envelope_left_part_x, 675);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(716 + envelope_left_part_x, 675);
    glVertex2f(716 + envelope_left_part_x, 615);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(716 + envelope_left_part_x, 615);
    glVertex2f(774 + envelope_left_part_x, 615);
    glEnd();
    // The right part of the stamp
    glBegin(GL_LINES);
    glVertex2f(774 + envelope_right_part_x, 615);
    glVertex2f(874 + envelope_right_part_x, 615);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(874 + envelope_right_part_x, 615);
    glVertex2f(874 + envelope_right_part_x, 675);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(874 + envelope_right_part_x, 675);
    glVertex2f(776 + envelope_right_part_x, 675);
    glEnd();
    // The word "STAMP"
    // The left part of the word
    setFont(40, ANSI_CHARSET, "MV Boli");
    glRasterPos2f(715 + envelope_left_part_x, 635);
    drawString(" S");
    glRasterPos2f(740 + envelope_right_part_x, 635);
    drawString(" T");
    glRasterPos2f(765 + envelope_right_part_x, 635);
    drawString(" A");
    glRasterPos2f(790 + envelope_right_part_x, 635);
    drawString(" M");
    glRasterPos2f(825 + envelope_right_part_x, 635);
    drawString(" P");

    // Draw the sentence on the bottom right of the envelope
    setFont(35, ANSI_CHARSET, "Freestyle Script");
    glRasterPos2f(610 + envelope_left_part_x, 210);
    drawString(" It's time to welcome");
    glRasterPos2f(760 + envelope_right_part_x, 210);
    drawString(" the new");
    glRasterPos2f(570 + envelope_left_part_x, 180);
    drawString(" year again. Wish you hav");
    glRasterPos2f(754 + envelope_right_part_x, 180);
    drawString(" e happy days");

    // Draw the sentence on the bottom left of the envelope
    setFont(45, ANSI_CHARSET, "Segoe Print");
    glRasterPos2f(138 + envelope_left_part_x, 310);
    drawString(" A");
    setFont(35, ANSI_CHARSET, "Segoe Print");
    glRasterPos2f(165 + envelope_left_part_x, 311);
    drawString(" S");
    setFont(45, ANSI_CHARSET, "Segoe Print");
    glRasterPos2f(180 + envelope_left_part_x, 310);
    drawString(" A");
    setFont(35, ANSI_CHARSET, "Segoe Print");
    glRasterPos2f(207 + envelope_left_part_x, 311);
    drawString(" D");
    setFont(45, ANSI_CHARSET, "Segoe Print");
    glRasterPos2f(225 + envelope_left_part_x, 310);
    drawString(" A");
    glRasterPos2f(250 + envelope_left_part_x, 310);
    drawString(" L ,");
    glRasterPos2f(305 + envelope_left_part_x, 310);
    drawString(" I");
    setFont(35, ANSI_CHARSET, "Segoe Print");
    glRasterPos2f(317 + envelope_left_part_x, 310);
    drawString(" n");
    setFont(35, ANSI_CHARSET, "Segoe Print");
    glRasterPos2f(332 + envelope_left_part_x, 310);
    drawString(" c");
    setFont(45, ANSI_CHARSET, "Segoe Print");
    glRasterPos2f(345 + envelope_left_part_x, 308);
    drawString(" .");
    setFont(30, ANSI_CHARSET, "Segoe Print");
    glRasterPos2f(140 + envelope_left_part_x, 280);
    drawString(" 111 Renai Road , Dushu Lake Science");
    glRasterPos2f(140 + envelope_left_part_x, 255);
    drawString(" and Education Innovation New District ,");
    glRasterPos2f(140 + envelope_left_part_x, 230);
    drawString(" Suzhou Industrial Park, Jiangsu Province");
    glRasterPos2f(140 + envelope_left_part_x, 205);
    drawString(" The People's Republic of China");
    glRasterPos2f(140 + envelope_left_part_x, 180);
    drawString(" 0512-88161888");

    glLoadIdentity();
    // The cover of the card
    glScalef(envelope_letter_x_scale, envelope_letter_y_scale, 0);
    glColor3ub(181, 41, 52);
    glBegin(GL_POLYGON);
    glVertex3f(1000 + envelope_letter_x2, 680, 0);
    glVertex3f(1770 + envelope_letter_x2, 680, 0);
    glVertex3f(1770 + envelope_letter_x2, 120, 0);
    glVertex3f(1000 + envelope_letter_x2, 120, 0);
    glEnd();
    // Greeting card cover frame
    glColor3ub(255, 198, 166);
    glBegin(GL_LINE_LOOP);
    glVertex3f(1070 + envelope_letter_x2, 650, 0);
    glVertex3f(1700 + envelope_letter_x2, 650, 0);
    glVertex3f(1700 + envelope_letter_x2, 150, 0);
    glVertex3f(1070 + envelope_letter_x2, 150, 0);
    glEnd();
    // Text in the middle of the greeting card cover
    glColor3ub(255, 215, 0);
    setFont(45, ANSI_CHARSET, "Eras Medium ITC");
    glRasterPos2f(1200 + envelope_letter_x2, 409);
    drawString(" New Year's Greeting Card");
}

void display(void) {
    gluOrtho2D(0, 1000, 0, 800);
    glClearColor(0.7098, 0.1608, 0.2039, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    drawFlower1(); drawFlower2(); drawFlower3(); drawFlower4(); drawFlower5(); drawFlower6();
    drawFlower7(); drawFlower8(); drawFlower9(); drawFlower10(); drawFlower11(); drawFlower12();

    drawBranch1(); drawBranch2(); drawBranch3(); drawBranch4(); drawBranch5();

    drawLantern1(); drawLantern2(); drawLantern3(); drawLantern4();
    drawLantern1Decoration(); drawLantern3Decoration(); drawLantern4Decoration();

    drawWord1(); drawWord2(); drawWord3();

    drawWordDecoration_star();
    drawWordDecoration_left1(); drawWordDecoration_left_leaves1(); drawWordDecoration_left_leaves2();
    drawWordDecoration_right1(); drawWordDecoration_right_leaves1(); drawWordDecoration_right_leaves2();
    drawWordDecoration_left2(); drawWordDecoration_left_leaves3(); drawWordDecoration_left_leaves4();
    drawWordDecoration_right2(); drawWordDecoration_right_leaves3(); drawWordDecoration_right_leaves4();

    drawFuWord1(); drawFuWord2();

    drawCandle1(); drawCandle2();

    drawMatch();

    drawFire1(); drawFire2();

    drawFrame();

    drawenvelopee();

    glutSwapBuffers();
}

// Main function to run the methods
int main(int argc, char* argv[]) {
    // The message alert
    MessageBox(NULL, ("1. Open the envelopee: Press left mouse button.\n"
        "2. Show the card: Press right mouse button.\n"
        "3. Light the candle: Press 'l' or 'L'.\n"
        "4. Quit: Press 'q' or 'Q'.\n"), ("Interactive action tips!"), MB_OK | MB_ICONINFORMATION);

    // Initialization the method
    glutInit(&argc, (char**)argv);

    // Design the location of the window
    glutInitWindowPosition(260, 8);

    // Design the size of the window
    glutInitWindowSize(1000, 800);

    // Design a window named "New Year's Greeting Card"
    glutCreateWindow("New Year's Greeting Card");

    // Draw the card in the window
    glutDisplayFunc(display);

    glutIdleFunc(when_in_mainloop);

    // The dynamic function
    glutTimerFunc(time_interval1, OnTimer_number_2023, 1);
    glutTimerFunc(time_interval3, OnTimer_FuWord, 1);
    glutTimerFunc(time_interval_envelope, onTimer_envelope, 1);

    // Call the "keyboard_input" function
    glutKeyboardFunc(keyboard_input);

    // The mouse callback function
    glutMouseFunc(mouse_input);

    // Enter the GLUT event processing loop
    glutMainLoop();

    // Return an integer value
    return 0;
}