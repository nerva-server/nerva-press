# Example Usage
Let's say we have a index.html file like:
```html
<h1>Hello!</h1>

What's up homie?

<%for(int i=0; i < 5; i++) { %>
<h2> Header <%-i%> </h2>
<% } %>

```
You can compile with that command:
```shell
nerva-press index.html -o output.hpp
```


# Example Inclusion
```C++
void someFunction() {
...
Server sv;

#include "path/to/generated/header/file"
sv.Use(NEVRA_PRESS_MAIN_ROUTER);
...
}
```
