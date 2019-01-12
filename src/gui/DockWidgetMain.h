/****************************************************************************//*
 * Copyright (C) 2019 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef DOCKWIDGETMAIN_H
#define DOCKWIDGETMAIN_H

////////////////////////////////////////////////////////////////////////////////

#include <QDockWidget>
#include <QSettings>

#include <fdm/fdm_DataInp.h>
#include <fdm/fdm_DataOut.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DockWidgetMain;
}

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Main dock widget class.
 */
class DockWidgetMain : public QDockWidget
{
    Q_OBJECT

public:

    /** Constructor. */
    explicit DockWidgetMain( QWidget *parent = 0 );

    /** Destructor. */
    virtual ~DockWidgetMain();

    /** */
    void setPhaseInp( fdm::DataInp::PhaseInp phaseInp );
    void setStateOut( fdm::DataOut::StateOut stateOut );

    void setTimeStep( double timeStep );

    void setFlightTime( QTime time );

protected:

    /** */
    void timerEvent( QTimerEvent *event );

signals:

    void phaseInpChanged( fdm::DataInp::PhaseInp phaseInp );


private:

    Ui::DockWidgetMain *m_ui;

    fdm::DataInp::PhaseInp m_phaseInp; ///< simulation input phase
    fdm::DataOut::StateOut m_stateOut; ///< simulation output state

    int m_timerId;                      ///< timer ID

    bool m_blink;                       ///<

private slots:

    void on_buttonPhaseInpIdle_clicked();
    void on_buttonPhaseInpInit_clicked();
    void on_buttonPhaseInpWork_clicked();
    void on_buttonPhaseInpPause_clicked();
    void on_buttonPhaseInpStop_clicked();
};

////////////////////////////////////////////////////////////////////////////////

#endif // DOCKWIDGETMAIN_H