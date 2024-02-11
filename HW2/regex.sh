#a
containsFoo='[Ff]oo'

#b
oneUpper='^[A-Z][a-z]+'

#c
emptyLines='^ *$'

#d
threeSets='([A-Za-z])\1.*([A-Za-z])\2.*([A-Za-z])\3'

#e
manyFlavors='fla(v|V)(o|O)(u|U)?(r|r)(i|I)?(n|N)?(g|G)?'

#f
mineMine='( [Mm]ine|   [Mm]ine){2,}$'

#g
dateRange='^19([2-9][8-9]|[3-9][0-9])-(0[1-9]|1[0-2])-(1[6-9]|2[0-9]|3[01])$'

#h
LastFirstAndMiddle='(([A-Z][a-z]+), ([A-Z][a-z]+) ([A-Z][a-z]+)$)|(([A-Z][a-z]+), ([A-Z][a-z]+) [A-Z].$)|(([A-Z][a-z]+), ([A-Z][a-z]+)$)'

#i
telephoneNumber='^([13579][0-9][0-9])-([0-9][0-9][0-9])-([0-9][0-9][0-9][0-9])$'

#j
doubleMatchQuoted='".*([A-Za-z].*){1,}"'

#k
romanNumeral='^(I{0,3}|VI{0,3}|IV|IX|X{0,3}(I{0,3}VI{0,3})?|XXXIX)$'