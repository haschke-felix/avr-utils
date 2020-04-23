#pragma once

/** template class to compose flags from enums in a type-safe fashion */

template <typename Inttype>
class IntFlags
{
	typedef Inttype Int;
	// static_assert((sizeof(Enum) <= sizeof(Int)), "Storage will overflow!");

public:
	// compiler-generated copy/move ctor/assignment operators are fine!

	// zero flags
	constexpr inline IntFlags() noexcept : i(Int(0)) {}
	// initialize from byte
	constexpr inline explicit IntFlags(Int i) : i(i) {}

	const inline IntFlags& operator&=(Int mask) noexcept {
		i &= mask;
		return *this;
	}

	const inline IntFlags& operator|=(IntFlags f) noexcept {
		i |= f.i;
		return *this;
	}
	const inline IntFlags& operator|=(Int mask) noexcept {
		i |= Int(mask);
		return *this;
	}
	const inline IntFlags& operator^=(IntFlags f) noexcept {
		i ^= f.i;
		return *this;
	}

	constexpr inline operator Int() const noexcept { return i; }

	constexpr inline IntFlags operator|(IntFlags f) const noexcept { return IntFlags(i | f.i); }
	constexpr inline IntFlags operator^(IntFlags f) const noexcept { return IntFlags(i ^ f.i); }
	constexpr inline IntFlags operator&(IntFlags f) const noexcept { return IntFlags(i & f.i); }
	constexpr inline IntFlags operator~() const noexcept { return IntFlags(~i); }

	constexpr inline bool operator!() const noexcept { return !i; }

	constexpr inline bool testFlag(Int f) const noexcept {
		return (i & Int(f)) == Int(f) && (Int(f) != 0 || i == Int(f));
	}

	inline IntFlags& setFlag(Int f, bool on = true) { /*return on ?*/
		on ? (*this |= f) : * this &= ~Int(f);
		return *this;
	}

	inline void clear() { i = 0; }

	// private:
	Int i;
};
