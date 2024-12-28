#include "ekran.h"
#include "matrix.h"

Ekran::Ekran(QWidget *parent)
    : QWidget{parent}
{

    m_img = QImage("Images/Obrazek1.jpg");
    m_canvas = QImage(1000, 1000, QImage::Format_RGB32);



    setupUI();

}

Ekran::~Ekran()
{
    m_mainLayout = nullptr;
    m_leftPanel = nullptr;
    m_rightPanel = nullptr;
    m_rightLayout = nullptr;
    m_combobox = nullptr;
    m_slider = nullptr;
    m_alphaLabel = nullptr;
    m_listWidget = nullptr;
    m_spacer = nullptr;
}

void Ekran::paintEvent(QPaintEvent *event)
{
    //QPainter p(this);
//
    //if (m_img.isNull())
    //{
    //    qDebug() << "Blad wczytania obrazu ";
    //    std::exit(-1);
    //}

    //p.drawImage(25, 25, m_img);

    // Tworzymy QPainter rysującego na m_canvas
    //QPainter canvasPainter(&m_canvas);
//
    //// Czyścimy płótno (opcjonalnie)
    //canvasPainter.fillRect(m_canvas.rect(), Qt::white);
//
    //// Rysujemy obraz m_img na płótnie w pozycji (x, y)
    //canvasPainter.drawImage(25, 25, m_img);

    //translation(360, 100);
    rotation(M_PI/4);
    //scaleX(2);
    //scaleY(2);
    //shearingX(-2);
    //shearingY(1);


    QPainter p(this);

    //p.fillRect(QRect(0, 0, 1000, 700), Qt::white);

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

    m_spacer = new QSpacerItem(20, 640, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_mainLayout->addItem(m_spacer);

    m_rightPanel = new QWidget(this);
    m_rightLayout = new QVBoxLayout(m_rightPanel);

    m_combobox = new QComboBox(this);
    m_combobox->addItem("Normal");
    m_combobox->addItem("Multiply");
    m_combobox->addItem("Screen");
    m_combobox->addItem("Overlay");
    m_combobox->addItem("Darken");
    m_combobox->addItem("Lighten");
    m_combobox->addItem("Difference");
    m_combobox->addItem("Additive");

    m_rightLayout->addWidget(m_combobox);

    m_alphaLabel = new QLabel("Alpha: 100", this);
    m_rightLayout->addWidget(m_alphaLabel);

    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(0, 100);
    m_slider->setValue(100);

    m_rightLayout->addWidget(m_slider);

    //connect(m_slider, &QSlider::valueChanged, this, &Ekran::updateLabel);
    //connect(m_slider, &QSlider::valueChanged, this, &Ekran::updateSliderValue);
    //connect(m_combobox, &QComboBox::currentTextChanged, this, &Ekran::updateMode);


    m_listWidget = new QListWidget(this);
    m_rightLayout->addWidget(m_listWidget);

    //connect(m_listWidget, &QListWidget::itemSelectionChanged, this, &Ekran::updateUI);

    m_rightPanel->setLayout(m_rightLayout);
    m_mainLayout->addWidget(m_rightPanel);

    setLayout(m_mainLayout);

}

void Ekran::translation(float translationX, float translationY)
{
    int ymax = m_img.height();
    int xmax = m_img.width();

    math::vec3 vec(translationX, translationY);

    math::mat3 matrix(1.0f);

    matrix = math::mat3::translation(matrix, vec);

    //matrix.print();

    for (int y = 0; y < ymax; y++)
    {
        for (int x = 0; x < xmax; x++)
        {
            PixelColor pixel = getPixel(m_img, x, y);

            math::vec3 vector(x, y);

            vector = matrix * vector;

            //qDebug() << "x: " << vector.x << " " << "y: " << vector.y;

            if (vector.x <= 0 || vector.x >= 1000 || vector.y <= 0 || vector.y >= 1000)
                continue;

            setPixel(m_canvas, vector.x, vector.y, pixel);
        }
    }
}

void Ekran::rotation(float radian)
{
    math::mat3 matrix(1.0f);
    matrix = math::mat3::rotation(matrix, radian);

    int ymax = m_img.height();
    int xmax = m_img.width();

    for (int y = 0; y < ymax; y++)
    {
        for (int x = 0; x < xmax; x++)
        {
            PixelColor pixel = getPixel(m_img, x, y);

            math::vec3 vector(x, y);

            vector = matrix * vector;

            //qDebug() << "x: " << vector.x << " " << "y: " << vector.y;

            if (vector.x <= 0 || vector.x >= 1000 || vector.y <= 0 || vector.y >= 1000)
                continue;

            setPixel(m_canvas, vector.x, vector.y, pixel);
        }
    }
}

void Ekran::scaleX(float x)
{
    math::mat3 matrix(1.0f);
    matrix = math::mat3::scaleX(matrix, x);

    int ymax = m_img.height();
    int xmax = m_img.width();

    for (int y = 0; y < ymax; y++)
    {
        for (int x = 0; x < xmax; x++)
        {
            PixelColor pixel = getPixel(m_img, x, y);

            math::vec3 vector(x, y);

            vector = matrix * vector;

            //qDebug() << "x: " << vector.x << " " << "y: " << vector.y;

            if (vector.x <= 0 || vector.x >= 1000 || vector.y <= 0 || vector.y >= 1000)
                continue;

            setPixel(m_canvas, vector.x, vector.y, pixel);
        }
    }
}

void Ekran::scaleY(float y)
{
    math::mat3 matrix(1.0f);
    matrix = math::mat3::scaleY(matrix, y);

    int ymax = m_img.height();
    int xmax = m_img.width();

    for (int y = 0; y < ymax; y++)
    {
        for (int x = 0; x < xmax; x++)
        {
            PixelColor pixel = getPixel(m_img, x, y);

            math::vec3 vector(x, y);

            vector = matrix * vector;

            //qDebug() << "x: " << vector.x << " " << "y: " << vector.y;

            if (vector.x <= 0 || vector.x >= 1000 || vector.y <= 0 || vector.y >= 1000)
                continue;

            setPixel(m_canvas, vector.x, vector.y, pixel);
        }
    }
}

void Ekran::shearingX(float value)
{
    math::mat3 matrix(1.0f);
    matrix = math::mat3::shearingX(matrix, value);

    int ymax = m_img.height();
    int xmax = m_img.width();

    for (int y = 0; y < ymax; y++)
    {
        for (int x = 0; x < xmax; x++)
        {
            PixelColor pixel = getPixel(m_img, x, y);

            math::vec3 vector(x, y);

            vector = matrix * vector;

            //qDebug() << "x: " << vector.x << " " << "y: " << vector.y;

            if (vector.x <= 0 || vector.x >= 1000 || vector.y <= 0 || vector.y >= 1000)
                continue;

            setPixel(m_canvas, vector.x, vector.y, pixel);
        }
    }
}

void Ekran::shearingY(float value)
{
    math::mat3 matrix(1.0f);
    matrix = math::mat3::shearingY(matrix, value);

    int ymax = m_img.height();
    int xmax = m_img.width();

    for (int y = 0; y < ymax; y++)
    {
        for (int x = 0; x < xmax; x++)
        {
            PixelColor pixel = getPixel(m_img, x, y);

            math::vec3 vector(x, y);

            vector = matrix * vector;

            //qDebug() << "x: " << vector.x << " " << "y: " << vector.y;

            if (vector.x <= 0 || vector.x >= 1000 || vector.y <= 0 || vector.y >= 1000)
                continue;

            setPixel(m_canvas, vector.x, vector.y, pixel);
        }
    }
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
