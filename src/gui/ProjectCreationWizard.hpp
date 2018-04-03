#ifndef GUI_PROJECTCREATIONWIZARD_HPP
#define GUI_PROJECTCREATIONWIZARD_HPP

#include <QWizard>
#include <memory>
#include <QLineEdit>
#include "OOProject.hpp"

namespace oonalysis::gui {

class ProjectCreationWizard : public QWizard {
public:
    ProjectCreationWizard();

    std::shared_ptr<OOProject> getCreatedProject() { return createdProject; }

private:
    QWizardPage* makeFilenamePage();
    std::shared_ptr<OOProject> createdProject;

    QLineEdit* pathField;
    QLineEdit* dbPathField;
    QLineEdit* rootPathField;

    void pathButtonClicked();
    void pathFieldChanged(const QString& text);
    void dbPathButtonClicked();
    void dbPathFieldChanged(const QString& text);
    void rootPathButtonClicked();
    void rootPathFieldChanged(const QString& text);

}; // class ProjectCreationWizard

} // namespace oonalysis::gui

#endif // GUI_PROJECTCREATIONWIZARD_HPP