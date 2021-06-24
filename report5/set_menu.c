#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "drink.h"

PriceList menu[] = { { "brewed", "Drip Coffee", { 319, 363, 407, 451}
                       },
{ "brewed", "Cafe Misto", { 374, 418, 462, 506}
  },
{ "espresso", "Late", { 374, 418, 462, 506}
  },
{ "espresso", "Soy Late", { 429, 473, 517, 561}
  },
{ "espresso", "Caramel Macchiato", { 429, 473, 517, 561}
  },
{ "espresso", "Cafe Mocha", { 440, 484, 528, 572}
  },
{ "espresso", "White Mocha", { 440, 484, 528, 572}
  },
{ "espresso", "Cafe Americano", { 341, 385, 429, 473}
  },
{ "espresso", "Cappuccino", { 374, 418, 462, 506}
  },
{ "frappuccino", "Dark Mocha Chip", { 0, 550, 594, 638}
  },
{ "frappuccino", "Coffee", { 0, 484, 528, 572}
  },
{ "frappuccino", "Caramel", { 0, 539, 583, 627}
  },
{ "frappuccino", "Dark Mocha Chip Cream", { 0, 550, 594, 638}
  },
{ "frappuccino", "Matcha cream", { 0, 539, 583, 627}
  },
{ "frappuccino", "Vanilla cream", { 0, 539, 583, 627}
  },
{ "frappuccino", "Mango Passion Tea", { 0, 517, 561, 605}
  },
{ "tea", "English Breakfast Tea Latte", { 440, 484, 528, 572}
  },
{ "tea", "Hojicha Tea Latte", { 440, 484, 528, 572}
  },
{ "tea", "Earl Gray Tea Latte", { 440, 484, 528, 572}
  },
{ "tea", "Chamomile Tea Latte", { 440, 484, 528, 572}
  },
{ "tea", "Matcha Tea Latte", { 440, 484, 528, 572}
  },
{ "tea", "Chai Tea Latte", { 440, 484, 528, 572}
  },
{ "tea", "Hot Tea", { 0, 374, 418, 462}
  },
{ "tea", "Iced Tea", { 330, 374, 418, 462}
  },
{ "others", "Cocoa", { 429, 473, 517, 561}
  },
{ "others", "Caramel Steamer", { 429, 473, 517, 561}
  }
};

unsigned no_of_drinks = sizeof(menu) / sizeof(PriceList);
char *cupsizename[] = { "Short", "Tall", "Grande", "Venti" };

PriceList *set_menu(char *kind)
{
  PriceList *p = menu;
  return p;
}
