/////////////////////////////////////////////////////////////////////////////
// Name:        plotps.cpp
// Purpose:     
// Author:      jean-pierre Charras
// Modified by: 
// Created:     01/02/2006 08:37:24
// RCS-ID:      
// Copyright:   GNU License
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 01/02/2006 08:37:24

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "plotps.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "fctsys.h"
#include "gr_basic.h"

#include "common.h"
#include "program.h"
#include "libcmp.h"
#include "general.h"
#include "worksheet.h"
#include "plot_common.h"
#include "protos.h"

#include "wx/defs.h"

// coeff de conversion dim en 1 mil -> dim en unite PS:
const double SCALE_PS = 0.001;

extern void Move_Plume( wxPoint pos, int plume );
extern void Plume( int plume );

enum PageFormatReq {
	PAGE_SIZE_AUTO,
	PAGE_SIZE_A4,
	PAGE_SIZE_A
};


/* Variables locales : */
static int PS_SizeSelect = PAGE_SIZE_AUTO;
extern FILE * PlotOutput;
static bool Plot_Sheet_Ref = TRUE;


////@begin includes
////@end includes

#include "plotps.h"

////@begin XPM images
////@end XPM images


/***********************************************************/
void WinEDA_SchematicFrame::ToPlot_PS(wxCommandEvent& event)
/***********************************************************/
/* fonction relai de creation de la frame de dialogue pour trace Postscript
*/
{
wxPoint pos;

	pos = GetPosition();
	pos.x += 10; pos.y += 20;
	WinEDA_PlotPSFrame * Ps_frame = new WinEDA_PlotPSFrame(this);
	Ps_frame->ShowModal(); Ps_frame->Destroy();
}



/*!
 * WinEDA_PlotPSFrame type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WinEDA_PlotPSFrame, wxDialog )

/*!
 * WinEDA_PlotPSFrame event table definition
 */

BEGIN_EVENT_TABLE( WinEDA_PlotPSFrame, wxDialog )

////@begin WinEDA_PlotPSFrame event table entries
    EVT_BUTTON( ID_PLOT_PS_CURRENT_EXECUTE, WinEDA_PlotPSFrame::OnPlotPsCurrentExecuteClick )

    EVT_BUTTON( ID_PLOT_PS_ALL_EXECUTE, WinEDA_PlotPSFrame::OnPlotPsAllExecuteClick )

    EVT_BUTTON( wxID_CLOSE, WinEDA_PlotPSFrame::OnCloseClick )

////@end WinEDA_PlotPSFrame event table entries

END_EVENT_TABLE()

/*!
 * WinEDA_PlotPSFrame constructors
 */

WinEDA_PlotPSFrame::WinEDA_PlotPSFrame( )
{
}

WinEDA_PlotPSFrame::WinEDA_PlotPSFrame( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

/*!
 * WinEDA_PlotPSFrame creator
 */

bool WinEDA_PlotPSFrame::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin WinEDA_PlotPSFrame member initialisation
    m_SizeOption = NULL;
    m_PlotPSColorOption = NULL;
    m_Plot_Sheet_Ref = NULL;
    m_DefaultLineSizeCtrlSizer = NULL;
    m_MsgBox = NULL;
////@end WinEDA_PlotPSFrame member initialisation

////@begin WinEDA_PlotPSFrame creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end WinEDA_PlotPSFrame creation
    return true;
}

/*!
 * Control creation for WinEDA_PlotPSFrame
 */

void WinEDA_PlotPSFrame::CreateControls()
{    
	SetFont(*g_DialogFont);
	
////@begin WinEDA_PlotPSFrame content construction
    // Generated by DialogBlocks, 22/01/2007 11:32:43 (unregistered)

    WinEDA_PlotPSFrame* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxString m_SizeOptionStrings[] = {
        _("Auto"),
        _("Page Size A4"),
        _("Page Size A")
    };
    m_SizeOption = new wxRadioBox( itemDialog1, ID_RADIOBOX1, _("Plot page size:"), wxDefaultPosition, wxDefaultSize, 3, m_SizeOptionStrings, 1, wxRA_SPECIFY_COLS );
    m_SizeOption->SetSelection(0);
    itemBoxSizer3->Add(m_SizeOption, 0, wxGROW|wxALL, 5);

    itemBoxSizer3->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer6Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Plot Options:"));
    wxStaticBoxSizer* itemStaticBoxSizer6 = new wxStaticBoxSizer(itemStaticBoxSizer6Static, wxVERTICAL);
    itemBoxSizer3->Add(itemStaticBoxSizer6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxString m_PlotPSColorOptionStrings[] = {
        _("B/W"),
        _("Color")
    };
    m_PlotPSColorOption = new wxRadioBox( itemDialog1, ID_RADIOBOX, _("Plot Color:"), wxDefaultPosition, wxDefaultSize, 2, m_PlotPSColorOptionStrings, 1, wxRA_SPECIFY_COLS );
    m_PlotPSColorOption->SetSelection(0);
    itemStaticBoxSizer6->Add(m_PlotPSColorOption, 0, wxGROW|wxALL, 5);

    m_Plot_Sheet_Ref = new wxCheckBox( itemDialog1, ID_CHECKBOX, _("Print Sheet Ref"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_Plot_Sheet_Ref->SetValue(false);
    itemStaticBoxSizer6->Add(m_Plot_Sheet_Ref, 0, wxGROW|wxALL, 5);

    itemBoxSizer3->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(itemBoxSizer10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton11 = new wxButton( itemDialog1, ID_PLOT_PS_CURRENT_EXECUTE, _("&Plot CURRENT"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton11->SetForegroundColour(wxColour(0, 128, 0));
    itemBoxSizer10->Add(itemButton11, 0, wxGROW|wxALL, 5);

    wxButton* itemButton12 = new wxButton( itemDialog1, ID_PLOT_PS_ALL_EXECUTE, _("Plot A&LL"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton12->SetForegroundColour(wxColour(179, 0, 0));
    itemBoxSizer10->Add(itemButton12, 0, wxGROW|wxALL, 5);

    wxButton* itemButton13 = new wxButton( itemDialog1, wxID_CLOSE, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton13->SetForegroundColour(wxColour(0, 0, 255));
    itemBoxSizer10->Add(itemButton13, 0, wxGROW|wxALL, 5);

    m_DefaultLineSizeCtrlSizer = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(m_DefaultLineSizeCtrlSizer, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText15 = new wxStaticText( itemDialog1, wxID_STATIC, _("Messages :"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText15, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

    m_MsgBox = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(-1, 200), wxTE_MULTILINE );
    itemBoxSizer2->Add(m_MsgBox, 0, wxGROW|wxALL|wxFIXED_MINSIZE, 5);

    // Set validators
    m_SizeOption->SetValidator( wxGenericValidator(& PS_SizeSelect) );
    m_PlotPSColorOption->SetValidator( wxGenericValidator(& g_PlotPSColorOpt) );
    m_Plot_Sheet_Ref->SetValidator( wxGenericValidator(& Plot_Sheet_Ref) );
////@end WinEDA_PlotPSFrame content construction

	m_DefaultLineSizeCtrl = new WinEDA_ValueCtrl(this, _("Default Line Width"), g_PlotPSMinimunLineWidth,
						g_UnitMetric, m_DefaultLineSizeCtrlSizer, EESCHEMA_INTERNAL_UNIT );

}

/*!
 * Should we show tooltips?
 */

bool WinEDA_PlotPSFrame::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WinEDA_PlotPSFrame::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WinEDA_PlotPSFrame bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WinEDA_PlotPSFrame bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WinEDA_PlotPSFrame::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WinEDA_PlotPSFrame icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WinEDA_PlotPSFrame icon retrieval
}
/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void WinEDA_PlotPSFrame::OnPlotPsCurrentExecuteClick( wxCommandEvent& event )
{
int Select_PlotAll = FALSE;

	InitOptVars();
	CreatePSFile(Select_PlotAll, PS_SizeSelect);
	m_MsgBox->AppendText( wxT("*****\n"));
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
 */

void WinEDA_PlotPSFrame::OnPlotPsAllExecuteClick( wxCommandEvent& event )
{
int Select_PlotAll = TRUE;

	InitOptVars();
	CreatePSFile(Select_PlotAll, PS_SizeSelect);
	m_MsgBox->AppendText( wxT("*****\n"));
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CLOSE
 */

void WinEDA_PlotPSFrame::OnCloseClick( wxCommandEvent& event )
{
	InitOptVars();
    Close(TRUE);
}


/*****************************************/
void WinEDA_PlotPSFrame::InitOptVars(void)
/*****************************************/
{
	Plot_Sheet_Ref = m_Plot_Sheet_Ref->GetValue();
	g_PlotPSColorOpt = m_PlotPSColorOption->GetSelection();
	PS_SizeSelect = m_SizeOption->GetSelection();
	g_PlotPSMinimunLineWidth = m_DefaultLineSizeCtrl->GetValue();
	if ( g_PlotPSMinimunLineWidth < 1 ) g_PlotPSMinimunLineWidth = 1;

}
 

/*************************************************************/
void WinEDA_PlotPSFrame::CreatePSFile(int AllPages, int pagesize)
/*************************************************************/
{
wxString PlotFileName, ShortFileName;
BASE_SCREEN *screen;
Ki_PageDescr * PlotSheet, * RealSheet;
int BBox[4];
wxPoint plot_offset;

	g_PlotFormat = PLOT_FORMAT_POST;

	/* Build the screen list */
	EDA_ScreenList ScreenList(NULL);

	if ( AllPages == TRUE ) screen = ScreenList.GetFirst();
	else screen = ActiveScreen;
	for ( ; screen != NULL; screen = ScreenList.GetNext() )
	{
		PlotSheet = screen->m_CurrentSheet;
		RealSheet = &g_Sheet_A4;
		if ( pagesize == PAGE_SIZE_AUTO ) RealSheet = PlotSheet;
		else if ( pagesize == PAGE_SIZE_A )	RealSheet = &g_Sheet_A;

		/* Calcul des limites de trace en 1/1000 pouce */
		BBox[0] = BBox[1] = g_PlotMargin;	// Plot margin in 1/1000 inch
		BBox[2] = RealSheet->m_Size.x - g_PlotMargin;
		BBox[3] = RealSheet->m_Size.y - g_PlotMargin;

		/* Calcul des echelles de conversion */
		g_PlotScaleX = SCALE_PS *
					(float) (BBox[2] - BBox[0]) /
					PlotSheet->m_Size.x;
		g_PlotScaleY = SCALE_PS *
					(float) (BBox[3] - BBox[1]) /
					PlotSheet->m_Size.y;

		plot_offset.x = 0;
		plot_offset.y = PlotSheet->m_Size.y;

		wxSplitPath(screen->m_FileName.GetData(), (wxString*) NULL,
				&ShortFileName, (wxString*) NULL);
		wxString dirbuf = wxGetCwd() + STRING_DIR_SEP;
		if( ! ShortFileName.IsEmpty() )
			PlotFileName = MakeFileName(dirbuf, ShortFileName, wxT(".ps"));
		else PlotFileName = MakeFileName(dirbuf, g_DefaultSchematicFileName, wxT(".ps"));

		PlotOneSheetPS(PlotFileName,screen, RealSheet, BBox, plot_offset);
		screen = (BASE_SCREEN*)screen->Pnext;
		if (AllPages == FALSE ) break;
	}
}


/*****************************************************************************************/
void WinEDA_PlotPSFrame::PlotOneSheetPS(const wxString & FileName,
			BASE_SCREEN * screen, Ki_PageDescr * sheet, int BBox[4], wxPoint plot_offset)
/*****************************************************************************************/
/* Trace en format PS. d'une feuille de dessin
*/
{
wxString Line;
EDA_BaseStruct *DrawList;
EDA_SchComponentStruct *DrawLibItem;
int layer;
wxPoint StartPos, EndPos;

	PlotOutput = wxFopen(FileName, wxT("wt"));
	if (PlotOutput == NULL)
	{
		Line = wxT("\n** ");
		Line += _("Unable to create ") + FileName + wxT(" **\n\n");
		m_MsgBox->AppendText(Line);
		wxBell();
		return ;
	}

	setlocale(LC_NUMERIC, "C");
	Line.Printf(_("Plot: %s\n"), FileName.GetData()) ;
	m_MsgBox->AppendText(Line);

	InitPlotParametresPS(plot_offset, sheet, g_PlotScaleX, g_PlotScaleY);
	SetDefaultLineWidthPS( g_PlotPSMinimunLineWidth);

	/* Init : */
	PrintHeaderPS( PlotOutput, wxT("EESchema-PS"), FileName, 1, BBox, wxLANDSCAPE );
	InitPlotParametresPS(plot_offset, sheet, 1.0, 1.0);

	if ( m_Plot_Sheet_Ref->GetValue() )
	{
		if ( (g_PlotFormat == PLOT_FORMAT_POST) && g_PlotPSColorOpt )
			SetColorMapPS ( BLACK );
		PlotWorkSheet(PLOT_FORMAT_POST, screen);
	}

	DrawList = screen->EEDrawList;
	while ( DrawList )	/* tracage */
	{
		Plume('U');
		layer = LAYER_NOTES;
		switch( DrawList->m_StructType )
		{
			case DRAW_BUSENTRY_STRUCT_TYPE :		/* Struct Raccord et Segment sont identiques */
				#undef STRUCT
				#define STRUCT ((DrawBusEntryStruct*)DrawList)
				StartPos = STRUCT->m_Pos;
				EndPos = STRUCT->m_End();
				layer = STRUCT->m_Layer;
			case DRAW_SEGMENT_STRUCT_TYPE :
				#undef STRUCT
				#define STRUCT ((EDA_DrawLineStruct*)DrawList)
				if ( DrawList->m_StructType == DRAW_SEGMENT_STRUCT_TYPE)
				{
					StartPos = STRUCT->m_Start;
					EndPos = STRUCT->m_End;
					layer = STRUCT->m_Layer;
				}
				if ( g_PlotPSColorOpt )
					SetColorMapPS ( ReturnLayerColor(layer) );
				switch (layer)
					{
					case LAYER_NOTES: /* Trace en pointilles */
						SetCurrentLineWidth(-1);
						fprintf(PlotOutput,"[50 50] 0 setdash\n");
						Move_Plume( StartPos, 'U');
						Move_Plume( EndPos, 'D');
						fprintf(PlotOutput,"[] 0 setdash\n");
						break;

					case LAYER_BUS:	/* Trait large */
						{
						fprintf(PlotOutput,"%d setlinewidth\n", g_PlotPSMinimunLineWidth * 3);
						Move_Plume( StartPos,'U');
						Move_Plume( EndPos,'D');
						fprintf(PlotOutput,"%d setlinewidth\n", g_PlotPSMinimunLineWidth);
						}
						break;

					default:
						SetCurrentLineWidth(-1);
						Move_Plume( StartPos,'U');
						Move_Plume( EndPos,'D');
						break;
					}
				break;

			case DRAW_JUNCTION_STRUCT_TYPE :
				#undef STRUCT
				#define STRUCT ((DrawJunctionStruct*)DrawList)
				if ( g_PlotPSColorOpt )
					SetColorMapPS (ReturnLayerColor(STRUCT->m_Layer) );
				PlotCercle( STRUCT->m_Pos, DRAWJUNCTION_SIZE);
				break;

			case DRAW_TEXT_STRUCT_TYPE :
			case DRAW_LABEL_STRUCT_TYPE :
			case DRAW_GLOBAL_LABEL_STRUCT_TYPE :
				PlotTextStruct(DrawList);
				break;

			case DRAW_LIB_ITEM_STRUCT_TYPE :
				DrawLibItem = (EDA_SchComponentStruct *) DrawList;
				PlotLibPart( DrawLibItem );
				break;

			case DRAW_PICK_ITEM_STRUCT_TYPE : break;
			case DRAW_POLYLINE_STRUCT_TYPE : break;
			case DRAW_SHEETLABEL_STRUCT_TYPE: break;
			case DRAW_MARKER_STRUCT_TYPE : break;

			case DRAW_SHEET_STRUCT_TYPE :
				#undef STRUCT
				#define STRUCT ((DrawSheetStruct*)DrawList)
				PlotSheetStruct(STRUCT);
				break;

			case DRAW_NOCONNECT_STRUCT_TYPE:
				#undef STRUCT
				#define STRUCT ((DrawNoConnectStruct*)DrawList)
				if ( g_PlotPSColorOpt )
					SetColorMapPS (ReturnLayerColor(LAYER_NOCONNECT) );
				PlotNoConnectStruct(STRUCT);
				break;

			default:
				break;
		}

		Plume('U');
		DrawList = DrawList->Pnext;
	}

	/* fin */
	CloseFilePS(PlotOutput);
	setlocale(LC_NUMERIC, "");

	m_MsgBox->AppendText( wxT("Ok\n"));
}

