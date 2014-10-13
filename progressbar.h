#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QProgressBar>
#include <QStatusBar>

class Progress_Bar
{
private:
    QProgressBar *p_bar;
    QStatusBar *s_bar;

public:
    Progress_Bar(int max_value, QStatusBar *status_bar);
    void finish();
    void upgrade(int value);
    void resize(int max);
};

#endif // PROGRESSBAR_H
