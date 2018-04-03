#include "ProjectCreationWizard.hpp"

#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QBoxLayout>
#include <QPushButton>
#include <QFileDialog>

namespace oonalysis::gui {

ProjectCreationWizard::ProjectCreationWizard() : QWizard() {
    createdProject = std::make_shared<OOProject>();
    addPage(makeFilenamePage());
}

QWizardPage* ProjectCreationWizard::makeFilenamePage() {
    auto page = new QWizardPage(this);
    auto layout = new QFormLayout(page);

    auto pathLayout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    auto pathField = new QLineEdit(page);
    this->pathField = pathField;
    connect(pathField, &QLineEdit::textChanged, this, &ProjectCreationWizard::pathFieldChanged);
    auto pathButton = new QPushButton("Select path", page);
    connect(pathButton, &QPushButton::clicked, this, &ProjectCreationWizard::pathButtonClicked);
    pathLayout->addWidget(pathField);
    pathLayout->addWidget(pathButton);
    layout->addRow("File Path", pathLayout);

    auto rootPathLayout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    auto rootPathField = new QLineEdit(page);
    this->rootPathField = rootPathField;
    connect(rootPathField, &QLineEdit::textChanged, this, &ProjectCreationWizard::rootPathFieldChanged);
    auto rootPathButton = new QPushButton("Select project root path", page);
    connect(rootPathButton, &QPushButton::clicked, this, &ProjectCreationWizard::rootPathButtonClicked);
    rootPathLayout->addWidget(rootPathField);
    rootPathLayout->addWidget(rootPathButton);
    layout->addRow("Project root file Path", rootPathLayout);

    auto dbPathLayout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    auto dbPathField = new QLineEdit(page);
    this->dbPathField = dbPathField;
    connect(dbPathField, &QLineEdit::textChanged, this, &ProjectCreationWizard::dbPathFieldChanged);
    auto dbPathButton = new QPushButton("Select project db path", page);
    connect(dbPathButton, &QPushButton::clicked, this, &ProjectCreationWizard::dbPathButtonClicked);
    dbPathLayout->addWidget(dbPathField);
    dbPathLayout->addWidget(dbPathButton);
    layout->addRow("Project database file Path", dbPathLayout);

    page->setLayout(layout);

    return page;
}

void ProjectCreationWizard::pathButtonClicked() {
    QString text = QFileDialog::getSaveFileName();
    pathField->setText(text);
}

void ProjectCreationWizard::pathFieldChanged(const QString &text) {
    createdProject->setProjectPath(text.toStdString());
}

void ProjectCreationWizard::rootPathButtonClicked() {
    QString text = QFileDialog::getExistingDirectory();
    rootPathField->setText(text);
}

void ProjectCreationWizard::rootPathFieldChanged(const QString &text) {
    createdProject->setRootPath(text.toStdString());
}

void ProjectCreationWizard::dbPathButtonClicked() {
    QString text = QFileDialog::getSaveFileName();
    dbPathField->setText(text);
}

void ProjectCreationWizard::dbPathFieldChanged(const QString &text) {
    createdProject->setDbPath(text.toStdString());
}

} // namespace oonalysis::gui