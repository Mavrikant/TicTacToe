#ifndef BUILDINFO_H
#define BUILDINFO_H

#include <QWidget>

namespace Ui
{
class BuildInfo;
}

class BuildInfo : public QWidget
{
    Q_OBJECT

  public:
    explicit BuildInfo(QWidget *parent = nullptr);
    ~BuildInfo();

  private:
    Ui::BuildInfo *ui;
};

#endif // BUILDINFO_H
