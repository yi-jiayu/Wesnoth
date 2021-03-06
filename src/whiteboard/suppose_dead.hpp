/* $Id: suppose_dead.hpp 49270 2011-04-18 20:16:54Z gabba $ */
/*
 Copyright (C) 2011 by Tommy Schmitz
 Part of the Battle for Wesnoth Project http://www.wesnoth.org

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY.

 See the COPYING file for more details.
 */

/**
 * @file
 */

#ifndef WB_SUPPOSE_DEAD_HPP_
#define WB_SUPPOSE_DEAD_HPP_

#include "action.hpp"
#include "map_location.hpp"

namespace wb {

	/**
	 * A planned action that temporarily removes a unit from the map
	 * for planning purposes
	 */
	class suppose_dead
	: public action
	, public boost::enable_shared_from_this<suppose_dead>
	{
		friend class validate_visitor;
		friend class highlight_visitor;

	public:
		///Future unit map must be valid during construction, so that suppose_dead can find its unit
		suppose_dead(size_t team_index, unit& curr_unit);
		virtual ~suppose_dead();

		/** Return the unit targeted by this action. Null if unit doesn't exist. */
		virtual unit* get_unit() const { return unit_; }
		/** Return the location at which this action was planned. */
		virtual map_location get_source_hex() const { return loc_; }

	//	Inherits from action
	//	{
			virtual std::ostream& print(std::ostream& s) const;

			virtual void accept(visitor& v);

			virtual bool execute();

			/** Applies temporarily the result of this action to the specified unit map. */
			virtual void apply_temp_modifier(unit_map& unit_map);
			/** Removes the result of this action from the specified unit map. */
			virtual void remove_temp_modifier(unit_map& unit_map);

			/** Gets called by display when drawing a hex, to allow actions to draw to the screen. */
			virtual void draw_hex(const map_location& hex);

			virtual bool is_numbering_hex(const map_location& hex) const;

			virtual void set_valid(bool valid);
			virtual bool is_valid() { return valid_; }
	//	}	End Inherits from action

	protected:
		unit* unit_;
		std::string unit_id_;
		map_location loc_;

		bool valid_;
	};

	/** Dumps a suppose_dead on a stream, for debug purposes. */
	std::ostream &operator<<(std::ostream &s, suppose_dead_ptr sup_d);
	std::ostream &operator<<(std::ostream &s, suppose_dead_const_ptr sup_d);
} // end namespace wb

#endif /* WB_SUPPOSE_DEAD_HPP_ */

