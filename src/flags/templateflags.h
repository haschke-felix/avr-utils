#pragma once

/** template class to compose flags from enums in a type-safe fashion */

template <typename Datatype, typename Enum>
class TemplateFlags
{
	typedef Datatype Int;
	//static_assert((sizeof(Enum) <= sizeof(Int)), "Storage will overflow!");

public:
	// compiler-generated copy/move ctor/assignment operators are fine!

	// zero flags
	constexpr inline TemplateFlags() noexcept : i(Int(0)) {}
	// initialization from single enum
	constexpr inline TemplateFlags(Enum f) noexcept : i(Int(f)) {}
	// initialize from byte
	constexpr inline explicit TemplateFlags(Int i) : i(i) {}

	const inline TemplateFlags& operator&=(Int mask) noexcept {
		i &= mask;
		return *this;
	}
	const inline TemplateFlags& operator&=(Enum mask) noexcept {
		i &= Int(mask);
		return *this;
	}
	const inline TemplateFlags& operator|=(TemplateFlags f) noexcept {
		i |= f.i;
		return *this;
	}
	const inline TemplateFlags& operator|=(Enum f) noexcept {
		i |= Int(f);
		return *this;
	}
	const inline TemplateFlags& operator|=(Int mask) noexcept {
		i |= Int(mask);
		return *this;
	}
	const inline TemplateFlags& operator^=(TemplateFlags f) noexcept {
		i ^= f.i;
		return *this;
	}
	const inline TemplateFlags& operator^=(Enum f) noexcept {
		i ^= Int(f);
		return *this;
	}

	constexpr inline operator Int() const noexcept { return i; }

	constexpr inline TemplateFlags operator|(TemplateFlags f) const noexcept { return TemplateFlags(i | f.i); }
	constexpr inline TemplateFlags operator|(Enum f) const noexcept { return TemplateFlags(i | Int(f)); }
	constexpr inline TemplateFlags operator^(TemplateFlags f) const noexcept { return TemplateFlags(i ^ f.i); }
	constexpr inline TemplateFlags operator^(Enum f) const noexcept { return TemplateFlags(i ^ Int(f)); }
	constexpr inline TemplateFlags operator&(Int mask) const noexcept { return TemplateFlags(i & mask); }
	constexpr inline TemplateFlags operator&(Enum f) const noexcept { return TemplateFlags(i & Int(f)); }
	constexpr inline TemplateFlags operator~() const noexcept { return TemplateFlags(~i); }

	constexpr inline bool operator!() const noexcept { return !i; }

	constexpr inline bool testFlag(Enum f) const noexcept {
		return (i & Int(f)) == Int(f) && (Int(f) != 0 || i == Int(f));
	}

	inline TemplateFlags& setFlag(Enum f, bool on = true) { /*return on ?*/
		on ? (*this |= f) : * this &= ~Int(f);
		return *this;
	}

	inline void clear() { i = 0; }

	// private:
	Int i;
};
