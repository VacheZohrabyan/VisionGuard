#include "label.h"

Label::Label()
{

}

std::vector<QLabel*> Label::getLabel() const noexcept
{
    return labels;
}

void Label::createLabel()
{
    Ui::MainWindow* ui = MainWindow::getUi();

    QLabel* label = new QLabel(this);
    label->setGeometry(10, 10, 400, 400);
    labels.push_back(label);
}
