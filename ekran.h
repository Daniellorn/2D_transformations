#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>

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

    PixelColor getPixel(const QImage& img, int x, int y) const;
    void setPixel(QImage& img, int x, int y, const PixelColor& color);

private:

    QImage m_img;
    QImage m_canvas;

    float m_sliderValue;
    QString m_selectedMode;
    QString m_selectedLayer;
    QListWidgetItem* m_selectedItem;

    QHBoxLayout* m_mainLayout;
    QWidget* m_leftPanel;
    QWidget* m_rightPanel;
    QVBoxLayout* m_rightLayout;
    QComboBox* m_combobox;
    QSlider* m_slider;
    QLabel* m_alphaLabel;
    QListWidget* m_listWidget;
    QSpacerItem* m_spacer;

signals:
};

#endif // EKRAN_H
