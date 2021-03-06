/****************************************************************************//*
 * Copyright (C) 2020 Marek M. Cel
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
#ifndef CGI_TRACES_H
#define CGI_TRACES_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Switch>

#include <fdm/fdm_DataOut.h>

#include <cgi/cgi_Module.h>

////////////////////////////////////////////////////////////////////////////////

namespace cgi
{

/** */
class Traces : public Module
{
public:

    /** Constructor. */
    Traces( const Module *parent = NULLPTR );

    /** Destructor. */
    virtual ~Traces();

    /** */
    void update();

    void reset();

    void setVisibility( bool visible );

private:

    osg::ref_ptr<osg::Switch> _switch;
    osg::ref_ptr<osg::Vec3Array> _positions;
    bool _visible;
    unsigned int _counter;
    fdm::DataOut::StateOut _prevState;

};

} // end of cgi namespace

////////////////////////////////////////////////////////////////////////////////

#endif // CGI_TRACES_H
