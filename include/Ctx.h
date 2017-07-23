#ifndef CTX_H
#define CTX_H

#include <vector>
#include <QUrl>
#include <QList>
#include "SrcFile.h"
#include "OOProg.h"
#include "guicontroller.h"


namespace oonalysis {

class Ctx
{
public:
    static Ctx* CTX();

    Ctx();

    OOProg gen_program();

    void add_files_from_selection(QList<QUrl> urls);

    GuiController* Controller;

private:
    void add_file(SrcFile& file);

    void add_file(const std::string& filename);

    std::vector<SrcFile> files;
}; // class Ctx

Ctx& CTX();

} // namespace oonalysis

#endif // CTX_H
