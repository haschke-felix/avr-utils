#pragma once

/** template class to compose flags from enums in a type-safe fashion */
template <typename Enum>
class Flags
{
	typedef unsigned int Int;
	static_assert((sizeof(Enum) <= sizeof(Int)), "Storage will overflow!");

public:
	// compiler-generated copy/move ctor/assignment operators are fine!

	// zero flags
	constexpr inline Flags() noexcept : i(Int(0)) {}
	// initialization from single enum
	constexpr inline Flags(Enum f) noexcept : i(Int(f)) {}
	// initialize from byte
	constexpr inline explicit Flags(Int i) : i(i) {}

	const inline Flags& operator&=(int mask) noexcept {
		i &= mask;
		return *this;
	}
	const inline Flags& operator&=(unsigned int mask) noexcept {
		i &= mask;
		return *this;
	}
	const inline Flags& operator&=(Enum mask) noexcept {
		i &= Int(mask);
		return *this;
	}
	const inline Flags& operator|=(Flags f) noexcept {
		i |= f.i;
		return *this;
	}
	const inline Flags& operator|=(Enum f) noexcept {
		i |= Int(f);
		return *this;
	}
	const inline Flags& operator|=(int mask) noexcept {
		i |= Int(mask);
		return *this;
	}
	const inline Flags& operator^=(Flags f) noexcept {
		i ^= f.i;
		return *this;
	}
	const inline Flags& operator^=(Enum f) noexcept {
		i ^= Int(f);
		return *this;
	}

	constexpr inline operator Int() const noexcept { return i; }

	constexpr inline Flags operator|(Flags f) const noexcept { return Flags(i | f.i); }
	constexpr inline Flags operator|(Enum f) const noexcept { return Flags(i | Int(f)); }
	constexpr inline Flags operator^(Flags f) const noexcept { return Flags(i ^ f.i); }
	constexpr inline Flags operator^(Enum f) const noexcept { return Flags(i ^ Int(f)); }
	constexpr inline Flags operator&(int mask) const noexcept { return Flags(i & mask); }
	constexpr inline Flags operator&(unsigned int mask) const noexcept { return Flags(i & mask); }
	constexpr inline Flags operator&(Enum f) const noexcept { return Flags(i & Int(f)); }
	constexpr inline Flags operator~() const noexcept { return Flags(~i); }

	constexpr inline bool operator!() const noexcept { return !i; }

	constexpr inline bool testFlag(Enum f) const noexcept {
		return (i & Int(f)) == Int(f) && (Int(f) != 0 || i == Int(f));
	}

	inline Flags& setFlag(Enum f, bool on = true) { /*return on ?*/
		on ? (*this |= f) : (*this &= ~Int(f));
		return *this;
	}

	inline void clear() { i = 0; }

	// private:
	Int i;
};

#define DECLARE_FLAGS(Flags, Enum) typedef Flags<Enum> Flags;
