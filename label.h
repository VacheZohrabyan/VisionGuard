#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include "mainwindow.h"

class Label
{
public:
    Label();

public:
    std::vector<QLabel*> getLabel() const noexcept;

private:
    createLabel() noexcept;

private:
    std::vector<QLabel*> labels;
};

#endif // LABEL_H
