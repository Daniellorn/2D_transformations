#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

struct PixelColor
{
    int R;
    int G;
    int B;
};


class Ekran : public QWidget
{
    Q_OBJECT
public:
    explicit Ekran(QWidget *parent = nullptr);
    ~Ekran();

protected:

    void paintEvent(QPaintEvent* event) override;

private:
    void setupUI();

    void translation(float translationX, float translationY);
    void rotation(float radian);
    void scaleX(float x);
    void scaleY(float y);
    void shearingX(float value);
    void shearingY(float value);

    void transform(float translationX, float translationY, float radian,
                   float scaleX, float scaleY, float shearingX, float shearingY);

    PixelColor getPixel(const QImage& img, int x, int y) const;
    void setPixel(QImage& img, int x, int y, const PixelColor& color);

private:

    QImage m_img;
    QImage m_canvas;

    QHBoxLayout* m_mainLayout;
    QWidget* m_leftPanel;
    QWidget* m_rightPanel;
    QVBoxLayout* m_rightLayout;

    QSlider* m_translateXSlider;
    QSlider* m_translateYSlider;
    QSlider* m_rotateSlider;
    QSlider* m_scaleXSlider;
    QSlider* m_scaleYSlider;
    QSlider* m_shearingXSlider;
    QSlider* m_shearingYSlider;

    QLabel* m_translationLabel;
    QLabel* m_rotateLabel;
    QLabel* m_scalingLabel;
    QLabel* m_shearingLabel;

    QPushButton* m_resetButton;

    QSpacerItem* m_spacer;

    int m_translateXValue;
    int m_translateYValue;
    float m_rotationValue;
    int m_scaleXValue;
    int m_scaleYValue;
    float m_shearXValue;
    float m_shearYValue;


private slots:
    void onTranslateXChanged(int value);
    void onTranslateYChanged(int value);
    void onRotationChanged(int value);
    void onScaleXChanged(int value);
    void onScaleYChanged(int value);
    void onShearXChanged(int value);
    void onShearYChanged(int value);

    void onButtonClicked();

signals:
};

#endif // EKRAN_H
