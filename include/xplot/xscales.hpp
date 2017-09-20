/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_SCALES_HPP
#define XPLOT_SCALES_HPP

#include "xtl/xoptional.hpp"

#include "xplot.hpp"

namespace xpl
{
    /*********************
     * scale declaration *
     *********************/

    template <class D>
    class xscale : public xplot<D>
    {
    public:

        using base_type = xplot<D>;
        using derived_type = D;

        xscale();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(bool, derived_type, reverse);
        XPROPERTY(bool, derived_type, allow_padding);

    private:

        void set_defaults();
    };

    /****************************
     * linear_scale declaration *
     ****************************/

    template <class D>
    class xlinear_scale : public xscale<D>
    {
    public:

        using base_type = xscale<D>;
        using derived_type = D;

        xlinear_scale();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(xtl::xoptional<double>, derived_type, min);
        XPROPERTY(xtl::xoptional<double>, derived_type, max);
        XPROPERTY(bool, derived_type, stabilized, false);
        XPROPERTY(double, derived_type, mid_range, 0.8);
        XPROPERTY(double, derived_type, min_range, 0.6);

    private:

        void set_defaults();
    };

    using linear_scale = xw::xmaterialize<xlinear_scale>;

    /*************************
     * log_scale declaration *
     *************************/

    template <class D>
    class xlog_scale : public xscale<D>
    {
    public:

        using base_type = xscale<D>;
        using derived_type = D;

        xlog_scale();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(xtl::xoptional<double>, derived_type, min);
        XPROPERTY(xtl::xoptional<double>, derived_type, max);

    private:

        void set_defaults();
    };

    using log_scale = xw::xmaterialize<xlog_scale>;

    /************************
     * scale implementation *
     ************************/

    template <class D>
    inline xscale<D>::xscale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xscale<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(reverse, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(allow_padding, patch);
    }

    template <class D>
    inline xeus::xjson xscale<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(reverse, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(allow_padding, state);

        return state;
    }

    template <class D>
    inline void xscale<D>::set_defaults()
    {
        this->_model_name() = "ScaleModel";
        this->_view_name() = "Scale";
    }

    /*******************************
     * linear_scale implementation *
     *******************************/

    template <class D>
    inline xlinear_scale<D>::xlinear_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlinear_scale<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(min, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(max, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(stabilized, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(mid_range, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(min_range, patch);
    }

    template <class D>
    inline xeus::xjson xlinear_scale<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(min, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(stabilized, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(mid_range, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(min_range, state);

        return state;
    }

    template <class D>
    inline void xlinear_scale<D>::set_defaults()
    {
        this->_model_name() = "LinearScaleModel";
        this->_view_name() = "LinearScale";
    }

    /****************************
     * log_scale implementation *
     ****************************/

    template <class D>
    inline xlog_scale<D>::xlog_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlog_scale<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(min, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(max, patch);
    }

    template <class D>
    inline xeus::xjson xlog_scale<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(min, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max, state);

        return state;
    }

    template <class D>
    inline void xlog_scale<D>::set_defaults()
    {
        this->_model_name() = "LogScaleModel";
        this->_view_name() = "LogScale";
    }
}

#endif
