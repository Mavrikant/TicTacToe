#include "buildinfo.h"
#include "config.h"
#include "git.h"
#include "ui_buildinfo.h"
#include <qstring.h>
BuildInfo::BuildInfo(QWidget *parent) : QWidget(parent), ui(new Ui::BuildInfo)
{
    ui->setupUi(this);
    ui->buildDate->setText(BUILD_DATE);
    if (GitMetadata::Populated())
    {
        ui->Branch->setText(QString::fromStdString(GitMetadata::Branch()));
        ui->commitDate->setText(QString::fromStdString(GitMetadata::CommitDate()));
        ui->commitHash->setText(QString::fromStdString(GitMetadata::CommitSHA1()));
        ui->authorName->setText(QString::fromStdString(GitMetadata::AuthorName()));
    }
    else
    {
        ui->Branch->setText("Git Not Found");
        ui->commitDate->setText("Git Not Found");
        ui->commitHash->setText("Git Not Found");
        ui->authorName->setText("Git Not Found");
    }
}

BuildInfo::~BuildInfo() { delete ui; }
