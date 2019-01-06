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
#ifndef FDM_LANDINGGEAR_H
#define FDM_LANDINGGEAR_H

////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <fdmMain/fdm_DataManager.h>
#include <fdmUtils/fdm_Vector3.h>
#include <fdmXml/fdm_XmlNode.h>

////////////////////////////////////////////////////////////////////////////////

namespace fdm
{

class Aircraft; ///< aircraft class forward declaration

/**
 * @brief Landing gear base class.
 *
 * <h5>XML configuration file format:</h5>
 * @code
 * <landing_gear>
 *   <wheel [steerable="{ 0|1 }"] [caster="{ 0|1 }"] [brake_group="{ 0|1|2 }]">
 *     <attachment_point> { [m] x-coordinate } { [m] y-coordinate } { [m] z-coordinate } </attachment_point>
 *     <unloaded_wheel> { [m] x-coordinate } { [m] y-coordinate } { [m] z-coordinate } </unloaded_wheel>
 *     <stiffness_coef> { [N/m] strut stiffness (spring) coefficient } </stiffness_coef>
 *     <damping_coef> { [N/(m/s)] strut damping coefficient  } </damping_coef>
 *     <friction_static> { [-] static friction coefficient } </friction_static>
 *     <friction_kinetic> { [-] kinetic friction coefficient } </friction_kinetic>
 *     <friction_rolling> { [-] rolling friction coefficient } </friction_rolling>
 *     [<max_angle> { [deg] max steering angle } </max_angle>]
 *   </wheel>
 *   ... { more wheels }
 * </landing_gear>
 * @endcode
 */
class FDMEXPORT LandingGear : public DataManager
{
public:

    /** Brake group. */
    enum BrakeGroup
    {
        None = 0,           ///< none
        Left,               ///< left brake group
        Right               ///< right brake group
    };

    /** Wheel data. */
    struct Wheel
    {
        Vector3 r_a_bas;    ///< [m] strut attachment point coordinates expressed in BAS
        Vector3 r_u_bas;    ///< [m] unloaded wheel coordinates expressed in BAS

        double k;           ///< [N/m] strut stiffness (spring) coefficient
        double c;           ///< [N/(m/s)] strut damping coefficient

        double mu_s;        ///< [-] coefficient of static friction
        double mu_k;        ///< [-] coefficient of kinetic friction
        double mu_r;        ///< [-] coefficient of rolling friction

        double angle_max;   ///< [rad] max turn angle

        bool steerable;     ///< specifies if wheel is steerable
        bool caster;        ///< specifies if wheel is caster

        BrakeGroup group;   ///< brake group
    };

    typedef std::vector< Wheel > Wheels;

    /**
     * Returns landing gear strut and ground plane intersection point.
     * @see http://paulbourke.net/geometry/pointlineplane/
     * @param b [m] landing gear strut attachment point coordinates (beginning)
     * @param e [m] landing gear unloaded wheel coordinates (end)
     * @param r [m] point on the ground plane coordinates
     * @param n [-] ground plane normal vector
     * @return [m] landing gear strut and ground plane intersection point
     */
    static Vector3 getIntersection( const Vector3 &b, const Vector3 &e,
                                    const Vector3 &r, const Vector3 &n );

    /**
     * Returns Pacejka "Magic Formula" coefficient.
     * @see https://en.wikipedia.org/wiki/Hans_B._Pacejka#The_Pacejka_%22Magic_Formula%22_tire_models
     * @see https://www.mathworks.com/help/physmod/sdl/ref/tireroadinteractionmagicformula.html
     * @param kappa [-] slip parameter (v_slip/v_roll)
     * @param b b coefficient
     * @param c c coefficient
     * @param d d coefficient
     * @param e e coefficient
     * @return Pacejka "Magic Formula" coefficient
     */
    static double getPacejkaCoef( double kappa,
                                  double b = 10.0, double c = 1.9,
                                  double d = 1.0,  double e = 0.97 );

    /** Constructor. */
    LandingGear( const Aircraft* aircraft );

    /** Destructor. */
    virtual ~LandingGear();

    /**
     * Reads data.
     * @param dataNode XML node
     */
    virtual void readData( XmlNode &dataNode );

    /**
     * Computes force and moment.
     */
    virtual void computeForceAndMoment();

    /**
     * Updates landing gear.
     */
    virtual void update() = 0;

    inline const Vector3& getFor_BAS() const { return m_for_bas; }
    inline const Vector3& getMom_BAS() const { return m_mom_bas; }

    inline bool getOnGround() const { return m_onGround; }

protected:

    const Aircraft *m_aircraft; ///< aircraft model main object

    Vector3 m_for_bas;          ///< [N] total force vector expressed in BAS
    Vector3 m_mom_bas;          ///< [N*m] total moment vector expressed in BAS

    Wheels m_wheels;            ///< wheels data

    double m_ctrlAngle;         ///< [rad] wheel turn angle

    double m_brake_l;           ///< [0.0,1.0] normalized brake force (left brake group)
    double m_brake_r;           ///< [0.0,1.0] normalized brake force (right brake group)

    bool m_antiskid;            ///< specifies if antiskid is enabled
    bool m_steering;            ///< specifies if steering is enabled

    bool m_onGround;            ///< specifies if aircraft is on the ground

    /**
     * Returns wheel ground reaction force.
     * @param wheel wheel data
     * @param surf_coef [-] surface dependent friction coefficient
     * @param vel_break [m/s] static friction breakaway velocity
     * @return [N] wheel ground reaction force
     */
    virtual Vector3 getWheelForce( const Wheel &wheel, const Vector3 &r_i_bas,
                                   double surf_coef = 1.0 , double vel_break = 1.0 );

    /**
     * Returns landing gear strut and ground plane intersection point expressed in BAS.
     * @param wheel wheel data
     * @return [m] landing gear strut and ground plane intersection point expressed in BAS
     */
    virtual Vector3 getWheelIsect( const Wheel &wheel );

private:

    /** Using this constructor is forbidden. */
    LandingGear( const LandingGear & ) : DataManager() {}
};

} // end of fdm namespace

////////////////////////////////////////////////////////////////////////////////

#endif // FDM_LANDINGGEAR_H
