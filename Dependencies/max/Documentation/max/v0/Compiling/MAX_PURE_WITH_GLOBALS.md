# MAX_PURE_WITH_GLOBALS

API version: [**v0**](../../v0.md)

## Note

MAX_PURE_WITH_GLOBALS allows a developer to provide aliasing information to the compiler.
A developer will want to be familiar with [pointer aliasing optimizations](AliasingOptimizations.md) in order to use MAX_PURE_WITH_GLOBALS.

A pure function is one that references or modifies only locals and arguments.
It cannot follow first-level indirections. This means no pointers or references.
Normally, this would mean not accessing globals either. However, this macro permits globals.

Use [MAX_PURE](MAX_PURE.md) instead if the code does not need to access globals.

Use [MAX_SEMI_PURE](MAX_SEMI_PURE.md) instead if the code needs to follow first-level indirections and does not need access to globals.

## Example

```c++
MAX_PURE_WITH_GLOBALS( void UpdateGlobalStats( int ElapsedTicks ) );

template< typename T >
MAX_PURE_WITH_GLOBALS( void UpdateGlobalStats( int ElapsedTicks, T ExtraInformation ) );
```

## Implementation

Go to [the implementation](../../../../Code/Include/max/Compiling/AliasingOptimizations.hpp#L30).