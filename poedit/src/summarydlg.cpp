/*

    poedit, a wxWindows i18n catalogs editor

    ---------------
      summarydlg.cpp
    
      Catalog update summary dialog
    
      (c) Vaclav Slavik, 2000

*/


#ifdef __GNUG__
#pragma implementation
#endif

#include <wx/wxprec.h>

#include <wx/xrc/xmlres.h>
#include <wx/config.h>
#include <wx/listbox.h>
#include <wx/stattext.h>
#include <wx/intl.h>

#include "summarydlg.h"


MergeSummaryDialog::MergeSummaryDialog(wxWindow *parent)
{
    wxTheXmlResource->LoadDialog(this, parent, "summary");
    wxRect r(wxConfig::Get()->Read("summary_pos_x", -1),
             wxConfig::Get()->Read("summary_pos_y", -1),
	     wxConfig::Get()->Read("summary_pos_w", -1),
             wxConfig::Get()->Read("summary_pos_h", -1));
    if (r.x != -1) SetSize(r);
}



MergeSummaryDialog::~MergeSummaryDialog()
{
    wxConfig::Get()->Write("summary_pos_x", (long)GetPosition().x);
    wxConfig::Get()->Write("summary_pos_y", (long)GetPosition().y);
    wxConfig::Get()->Write("summary_pos_w", (long)GetSize().x);
    wxConfig::Get()->Write("summary_pos_h", (long)GetSize().y);
}



void MergeSummaryDialog::TransferTo(const wxArrayString& snew, const wxArrayString& sobsolete)
{
    wxString sum;
    sum.Printf(_("(%i new, %i obsolete)"), 
               snew.GetCount(), sobsolete.GetCount());
    XMLCTRL(*this, "items_count", wxStaticText)->SetLabel(sum);

    wxListBox *listbox;
    size_t i;
    
    listbox = XMLCTRL(*this, "new_strings", wxListBox);
    for (i = 0; i < snew.GetCount(); i++)
        listbox->Append(snew[i]);

    listbox = XMLCTRL(*this, "obsolete_strings", wxListBox);
    for (i = 0; i < sobsolete.GetCount(); i++)
        listbox->Append(sobsolete[i]);
}
