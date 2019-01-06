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
#ifndef FDM_TABLE_H
#define FDM_TABLE_H

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include <fdmMain/fdm_Defines.h>

////////////////////////////////////////////////////////////////////////////////

namespace fdm
{

/**
 * @brief Table and linear interpolation class.
 */
class FDMEXPORT Table
{
public:

    /**
     * @brief Creates table with only one record.
     * @param val value
     */
    static Table createOneRecordTable( double val = 0.0 );

    /** Constructor. */
    Table();

    /** Constructor. */
    Table( const std::vector< double > &keyValues,
           const std::vector< double > &tableData );

    /** Copy constructor. */
    Table( const Table &table );

    /** Destructor. */
    virtual ~Table();

    /**
     * Returns key value for the given key index.
     * @param keyIndex key index
     * @return key value on success or NaN on failure
     */
    double getIndexValue( unsigned int keyIndex ) const;

    /** */
    inline unsigned int getSize() const { return m_size; }

    /**
     * Returns key of minimum table value.
     * @return key of minimum table value
     */
    double getKeyOfValueMin() const;

    /**
     * Returns key of maximum table value.
     * @return key of maximum table value
     */
    double getKeyOfValueMax() const;

    /**
     * Returns table value for the given key value using linear
     * interpolation algorithm.
     * @param keysValue key value
     * @return interpolated value on success or NaN on failure
     */
    double getValue( double keyValue ) const;

    /**
     * Returns table value for the given key index.
     * @param keyIndex key index
     * @return value on success or NaN on failure
     */
    double getValueByIndex( unsigned int keyIndex ) const;

    /** */
    double getValueFirst() const;

    /** */
    double getValueLast() const;

    /**
     * Returns minimum table value.
     * @return minimum table value
     */
    double getValueMin() const;

    /**
     * Returns maximum table value.
     * @return maximum table value
     */
    double getValueMax() const;

    /** */
    bool isValid() const;

    /**
     * Returns string representation of the table.
     */
    std::string toString();

    /** Assignment operator. */
    const Table& operator= ( const Table &table );

private:

    unsigned int m_size;    ///< number of table elements

    double *m_keyValues;    ///< key values
    double *m_tableData;    ///< table data

    double *m_interpolData; ///< interpolation data matrix

    /** Updates interpolation data due to table data. */
    void updateInterpolationData();
};

} // end of fdm namespace

////////////////////////////////////////////////////////////////////////////////

#endif // FDM_TABLE_H
