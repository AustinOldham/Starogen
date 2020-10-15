- In the configuration files, solids are in units of zettagrams.


## Notes

- chance\_multiplier: Default is 1. A multiplier of 0.5 would give that resource a 50% chance of being on a given planet
- abundance\_multiplier: Default is 1. Since the adjective for a resource's abundance is based on what percentage of a planet is made of that resource, the abundance multiplier is used to account for more rare materials. A multiplier of 0.1 would be given to something that is 1/10 as common as a normal resource.
- Adjectives are determined by taking the percentage of total mass of a resource, dividing it by abundance\_multiplier, and choosing the first number it is less than or equal to.