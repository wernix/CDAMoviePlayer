#include "progressbar.h"

#include "ui_mainwindow.h"

Progress_Bar::Progress_Bar(int max_value, QStatusBar *status_bar) : p_bar(new QProgressBar),
    s_bar(status_bar)
{
    s_bar->addWidget(p_bar);
    p_bar->setMaximum(max_value);
    p_bar->setAlignment(Qt::AlignLeft);
    p_bar->setMaximumSize(180, 19);
    p_bar->show();
}

void Progress_Bar::finish()
{
    int max = p_bar->maximum();
    p_bar->setValue(max);
    p_bar->hide();
}

void Progress_Bar::upgrade(int value)
{
    int cur = p_bar->value();
    p_bar->setValue(cur+value);
}

void Progress_Bar::resize(int max)
{
    p_bar->setMaximum(max);
}
