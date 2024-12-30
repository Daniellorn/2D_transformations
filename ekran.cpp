#include "ekran.h"
#include "matrix.h"

Ekran::Ekran(QWidget *parent)
    : QWidget{parent}, m_translateXValue(0), m_translateYValue(0),
    m_rotationValue(0), m_scaleXValue(1), m_scaleYValue(1), m_shearXValue(0),
    m_shearYValue(0)
{

    m_img = QImage("Images/Obrazek1.png");
    m_canvas = QImage(900, 700, QImage::Format_RGB32);
    m_canvas.fill(Qt::white);



    setupUI();

     transform(0, 0, 0, 1, 1, 0, 0);
}

Ekran::~Ekran()
{
    m_mainLayout = nullptr;
    m_leftPanel = nullptr;
    m_rightPanel = nullptr;
    m_rightLayout = nullptr;
    m_translateXSlider = nullptr;
    m_translateYSlider = nullptr;
    m_translationLabel = nullptr;
    m_rotateLabel = nullptr;
    m_rotateSlider = nullptr;
    m_scalingLabel = nullptr;
    m_scaleXSlider = nullptr;
    m_scaleYSlider = nullptr;
    m_shearingXSlider = nullptr;
    m_shearingYSlider = nullptr;
    m_shearingLabel = nullptr;
    m_spacer = nullptr;
}

void Ekran::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    if (m_img.isNull())
    {
        qDebug() << "Blad wczytania obrazu ";
        std::exit(-1);
    }

    p.drawImage(25, 25, m_canvas);

}

void Ekran::setupUI()
{
    m_mainLayout = new QHBoxLayout(this);

    m_leftPanel = new QWidget(this);
    m_leftPanel->setMinimumSize(1000, 700);
    m_mainLayout->addWidget(m_leftPanel);

    //m_spacer = new QSpacerItem(5, 100, QSizePolicy::Expanding, QSizePolicy::Expanding);
    //m_mainLayout->addItem(m_spacer);

    m_rightPanel = new QWidget(this);
    m_rightLayout = new QVBoxLayout(m_rightPanel);
    m_rightPanel->setMinimumSize(300, 750);

    m_translationLabel = new QLabel("Translation", this);
    m_rightLayout->addWidget(m_translationLabel);

    m_translateXSlider = new QSlider(Qt::Horizontal, this);
    m_translateXSlider->setRange(-m_canvas.width()/2, m_canvas.width()/2);
    m_translateXSlider->setMinimumWidth(0);
    m_translateXSlider->setValue(0);
    m_translateYSlider = new QSlider(Qt::Horizontal, this);
    m_translateYSlider->setRange(-m_canvas.height()/2, m_canvas.height()/2);
    m_translateYSlider->setValue(0);
    m_rightLayout->addWidget(m_translateXSlider);
    m_rightLayout->addWidget(m_translateYSlider);

    m_rotateLabel = new QLabel("Rotation", this);
    m_rightLayout->addWidget(m_rotateLabel);

    m_rotateSlider = new QSlider(Qt::Horizontal, this);
    m_rotateSlider->setRange(0, 360);
    m_rightLayout->addWidget(m_rotateSlider);

    m_scalingLabel = new QLabel("Scale", this);
    m_rightLayout->addWidget(m_scalingLabel);

    m_scaleXSlider = new QSlider(Qt::Horizontal, this);
    m_scaleXSlider->setRange(-100, 100);
    m_scaleXSlider->setValue(0);
    m_scaleYSlider = new QSlider(Qt::Horizontal, this);
    m_scaleYSlider->setRange(-100, 100);
    m_scaleYSlider->setValue(0);
    m_rightLayout->addWidget(m_scaleXSlider);
    m_rightLayout->addWidget(m_scaleYSlider);

    m_shearingLabel = new QLabel("Shearing", this);
    m_rightLayout->addWidget(m_shearingLabel);

    m_shearingXSlider = new QSlider(Qt::Horizontal, this);
    m_shearingXSlider->setRange(-100, 100);
    m_shearingXSlider->setValue(0);
    m_shearingYSlider = new QSlider(Qt::Horizontal, this);
    m_shearingYSlider->setRange(-100, 100);
    m_shearingYSlider->setValue(0);
    m_rightLayout->addWidget(m_shearingXSlider);
    m_rightLayout->addWidget(m_shearingYSlider);

    m_resetButton = new QPushButton("Reset", this);
    m_rightLayout->addWidget(m_resetButton);

    m_rightPanel->setLayout(m_rightLayout);
    m_mainLayout->addWidget(m_rightPanel);

    setLayout(m_mainLayout);

    connect(m_translateXSlider, &QSlider::valueChanged, this, &Ekran::onTranslateXChanged);
    connect(m_translateYSlider, &QSlider::valueChanged, this, &Ekran::onTranslateYChanged);
    connect(m_rotateSlider, &QSlider::valueChanged, this, &Ekran::onRotationChanged);
    connect(m_scaleXSlider, &QSlider::valueChanged, this, &Ekran::onScaleXChanged);
    connect(m_scaleYSlider, &QSlider::valueChanged, this, &Ekran::onScaleYChanged);
    connect(m_shearingXSlider, &QSlider::valueChanged, this, &Ekran::onShearXChanged);
    connect(m_shearingYSlider, &QSlider::valueChanged, this, &Ekran::onShearYChanged);


    connect(m_resetButton, &QPushButton::clicked, this, &Ekran::onButtonClicked);

}

void Ekran::transform(float translationX, float translationY, float radian, float scaleX, float scaleY, float shearingX, float shearingY)
{
    math::vec3 imgCenter(-m_img.width() / 2, -m_img.height() / 2);

    math::mat3 translationToZero(1.0f);
    translationToZero = math::mat3::translation(translationToZero, imgCenter);

    math::mat3 scaleMatrix(1.0f);
    math::vec3 vec(scaleX, scaleY);
    scaleMatrix = math::mat3::scaleXY(scaleMatrix, vec);

    math::mat3 shearingXMatrix(1.0f);
    shearingXMatrix = math::mat3::shearingX(shearingXMatrix, shearingX);

    math::mat3 shearingYMatrix(1.0f);
    shearingYMatrix = math::mat3::shearingY(shearingYMatrix, shearingY);

    math::mat3 rotationMatrix(1.0f);
    rotationMatrix = math::mat3::rotation(rotationMatrix, radian);

    math::mat3 translationMatrix(1.0f);
    math::vec3 translationVec(translationX, translationY);
    translationMatrix = math::mat3::translation(translationMatrix, translationVec);

    math::vec3 translationCenter(m_img.width() / 2, m_img.height() / 2);
    math::mat3 translationToCenter(1.0f);
    translationToCenter = math::mat3::translation(translationToCenter, translationCenter);

    math::mat3 transformationMatrix;

    float imgCenterX = m_img.width() / 2.0f;
    float imgCenterY = m_img.height() / 2.0f;

    float canvasCenterX = m_canvas.width() / 2.0f;
    float canvasCenterY = m_canvas.height() / 2.0f;

    float displacementVecX = canvasCenterX - imgCenterX;
    float displacementVecY = canvasCenterY - imgCenterY;

    math::vec3 displacementVec(displacementVecX, displacementVecY);
    math::mat3 displacementMatrix(1.0f);
    displacementMatrix = math::mat3::translation(displacementMatrix, displacementVec);

    //transformationMatrix = translationToCenter * translationMatrix * rotationMatrix *
    //                       shearingYMatrix * shearingXMatrix * scaleMatrix * translationToZero;

   // transformationMatrix = translationToZero * scaleMatrix * shearingXMatrix *
   //                        shearingYMatrix * rotationMatrix * translationMatrix * translationToCenter;


    transformationMatrix = translationToZero * scaleMatrix * rotationMatrix * shearingXMatrix *
                           shearingYMatrix * translationMatrix * translationToCenter * displacementMatrix;

    int xmax = m_canvas.width();
    int ymax = m_canvas.height();
    PixelColor imgColor;

    m_canvas.fill(Qt::white);

    for (int y = 0; y < ymax; y++)
    {
        for (int x = 0; x < xmax; x++)
        {

            math::vec3 vector(x, y);

            vector = transformationMatrix * vector;

            if (std::ceil(vector.x) > 0 && std::ceil(vector.x) < m_img.width() && std::ceil(vector.y) > 0 && std::ceil(vector.y) < m_img.height())
            {
                //imgColor = getPixel(m_img, vector.x, vector.y);

                float a = vector.x - std::floor(vector.x);
                float b = vector.y - std::floor(vector.y);

                PixelColor P1 = getPixel(m_img, std::floor(vector.x), std::ceil(vector.y));
                PixelColor P2 = getPixel(m_img, std::ceil(vector.x), std::ceil(vector.y));
                PixelColor P3 = getPixel(m_img, std::ceil(vector.x), std::floor(vector.y));
                PixelColor P4 = getPixel(m_img, std::floor(vector.x), std::floor(vector.y));

                imgColor.R = b * ((1 - a) * P1.R + a * P2.R) + (1 - b) * ((1 - a) * P4.R + a * P3.R);
                imgColor.G = b * ((1 - a) * P1.G + a * P2.G) + (1 - b) * ((1 - a) * P4.G + a * P3.G);
                imgColor.B = b * ((1 - a) * P1.B + a * P2.B) + (1 - b) * ((1 - a) * P4.B + a * P3.B);

            }
            else
            {
                imgColor = PixelColor(255, 255, 255);
            }


           if (x > 0 && x < xmax && y > 0 && y < ymax)
            {
                setPixel(m_canvas, x, y, imgColor);
            }
        }
    }

    update();
}

PixelColor Ekran::getPixel(const QImage &img, int x, int y) const
{
    const uchar* line = img.scanLine(y);
    uint8_t blue = line[4*x]; //blue
    uint8_t green = line[4*x + 1]; //green
    uint8_t red = line[4*x + 2]; //red
    //uint8_t alpha = line[4*x + 3]; // alpha


    return PixelColor{red, green, blue};
}

void Ekran::setPixel(QImage &img, int x, int y, const PixelColor &color)
{
    int red = color.R;
    int green = color.G;
    int blue = color.B;

    uchar* line = img.scanLine(y);
    line[4*x] = blue; //blue
    line[4*x + 1] = green; //green
    line[4*x + 2] = red; //red
    //line[4*x + 3] = 255; // alpha
}

void Ekran::onTranslateXChanged(int value)
{
    m_translateXValue = value;
    transform(m_translateXValue, m_translateYValue, m_rotationValue,
              m_scaleXValue, m_scaleYValue, m_shearXValue, m_shearYValue);
}

void Ekran::onTranslateYChanged(int value)
{
    m_translateYValue = value;
    transform(m_translateXValue, m_translateYValue, m_rotationValue,
              m_scaleXValue, m_scaleYValue, m_shearXValue, m_shearYValue);
}

void Ekran::onRotationChanged(int value)
{
    m_rotationValue = value * M_PI / 180;
    transform(m_translateXValue, m_translateYValue, m_rotationValue,
              m_scaleXValue, m_scaleYValue, m_shearXValue, m_shearYValue);
}

void Ekran::onScaleXChanged(int value)
{
    m_scaleXValue = value;
    transform(m_translateXValue, m_translateYValue, m_rotationValue,
              m_scaleXValue, m_scaleYValue, m_shearXValue, m_shearYValue);
}

void Ekran::onScaleYChanged(int value)
{
    m_scaleYValue = value;
    transform(m_translateXValue, m_translateYValue, m_rotationValue,
              m_scaleXValue, m_scaleYValue, m_shearXValue, m_shearYValue);
}

void Ekran::onShearXChanged(int value)
{
    m_shearXValue = value / 100.0f;
    transform(m_translateXValue, m_translateYValue, m_rotationValue,
              m_scaleXValue, m_scaleYValue, m_shearXValue, m_shearYValue);
}

void Ekran::onShearYChanged(int value)
{
    m_shearYValue = value / 100.0f;
    transform(m_translateXValue, m_translateYValue, m_rotationValue,
              m_scaleXValue, m_scaleYValue, m_shearXValue, m_shearYValue);
}

void Ekran::onButtonClicked()
{
    m_translateXValue = 0;
    m_translateYValue = 0;
    m_rotationValue = 0;
    m_scaleXValue = 1;
    m_scaleYValue = 1;
    m_shearXValue = 0.0f;
    m_shearYValue = 0.0f;

    m_translateXSlider->setValue(0);
    m_translateYSlider->setValue(0);
    m_rotateSlider->setValue(0);
    m_scaleXSlider->setValue(1);
    m_scaleYSlider->setValue(1);
    m_shearingXSlider->setValue(0);
    m_shearingYSlider->setValue(0);

    transform(m_translateXValue, m_translateYValue, m_rotationValue,
              m_scaleXValue, m_scaleYValue, m_shearXValue, m_shearYValue);

}
