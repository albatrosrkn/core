/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */
#ifndef INCLUDED_SVX_ITEMWIN_HXX
#define INCLUDED_SVX_ITEMWIN_HXX

#include <vcl/field.hxx>
#include <vcl/lstbox.hxx>
#include <sfx2/InterimItemWindow.hxx>
#include <svtools/toolbarmenu.hxx>
#include <svx/dlgctrl.hxx>
#include <svx/svxdllapi.h>

class XLineWidthItem;
class SfxObjectShell;
class SvtValueSet;
class SvxLineStyleToolBoxControl;

class SvxLineBox final : public WeldToolbarPopup
{
    rtl::Reference<SvxLineStyleToolBoxControl> mxControl;
    std::unique_ptr<SvtValueSet> mxLineStyleSet;
    std::unique_ptr<weld::CustomWeld> mxLineStyleSetWin;

    void FillControl();
    void Fill(const XDashListRef &pList);

    DECL_LINK(SelectHdl, SvtValueSet*, void);

    virtual void GrabFocus() override;

public:
    SvxLineBox(SvxLineStyleToolBoxControl* pControl, weld::Widget* pParent, int nInitialIndex);
    virtual ~SvxLineBox() override;
};

class SVX_DLLPUBLIC SvxMetricField final : public InterimItemWindow
{
private:
    std::unique_ptr<weld::MetricSpinButton> m_xWidget;
    int             nCurValue;
    MapUnit         ePoolUnit;
    FieldUnit       eDlgUnit;
    css::uno::Reference< css::frame::XFrame > mxFrame;

    DECL_LINK(ModifyHdl, weld::MetricSpinButton&, void);
    DECL_LINK(KeyInputHdl, const KeyEvent&, bool);
    DECL_LINK(FocusInHdl, weld::Widget&, void);

    static void     ReleaseFocus_Impl();

    virtual void    DataChanged( const DataChangedEvent& rDCEvt ) override;

    virtual void GetFocus() override;

public:
    SvxMetricField( vcl::Window* pParent,
                    const css::uno::Reference< css::frame::XFrame >& rFrame );
    virtual void dispose() override;
    virtual ~SvxMetricField() override;

    void            Update( const XLineWidthItem* pItem );
    void            SetCoreUnit( MapUnit eUnit );
    void            RefreshDlgUnit();

    void            set_sensitive(bool bSensitive);
};

class SVX_DLLPUBLIC SvxFillTypeBox final : public ListBox
{
public:
    SvxFillTypeBox( vcl::Window* pParent );

    void Fill();

    static void Fill(weld::ComboBox& rListBox);

    void            Selected() { bSelect = true; }
    virtual boost::property_tree::ptree DumpAsPropertyTree() override;

private:
    virtual bool    PreNotify( NotifyEvent& rNEvt ) override;
    virtual bool    EventNotify( NotifyEvent& rNEvt ) override;

    sal_uInt16      nCurPos;
    bool            bSelect;

    static void     ReleaseFocus_Impl();
};

class SVX_DLLPUBLIC SvxFillAttrBox final : public ListBox
{
public:
    SvxFillAttrBox( vcl::Window* pParent );

    void Fill( const XHatchListRef    &pList );
    void Fill( const XGradientListRef &pList );
    void Fill( const XBitmapListRef   &pList );
    void Fill( const XPatternListRef  &pList );

    static void Fill(weld::ComboBox&, const XHatchListRef &pList);
    static void Fill(weld::ComboBox&, const XGradientListRef &pList);
    static void Fill(weld::ComboBox&, const XBitmapListRef &pList);
    static void Fill(weld::ComboBox&, const XPatternListRef &pList);

private:
    virtual bool    PreNotify( NotifyEvent& rNEvt ) override;
    virtual bool    EventNotify( NotifyEvent& rNEvt ) override;

    sal_uInt16      nCurPos;
    BitmapEx        maBitmapEx;

    static void     ReleaseFocus_Impl();
};

#endif // INCLUDED_SVX_ITEMWIN_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
