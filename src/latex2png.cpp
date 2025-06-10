#include "MicroTeX/platform/cairo/graphic_cairo.h"
#include "MicroTeX/latex.h"
#include <gtkmm.h>
#include <iostream>
#include <string>

using namespace tex;

/**
 * Class used to initiate LaTeX
 */
class TexGuard {
public:
    TexGuard() {
        LaTeX::init();
    }

};
/**
 * Function that uses MicroTeX to generate problem pngs for Manki
 *
 * @param code the LaTeX code to be turned into an image
 * @param file the name of the png file to create
 *
 * @return 0
 */
int generate_png(std::wstring& code, std::string& file) {
        TexGuard texGuard;
        auto r = LaTeX::parse(code, 720, 20, 10, BLACK);
        const float w = r->getWidth() + 11 * 2;
        const float h = r->getHeight() + 11 * 2;
        auto surface = Cairo::SvgSurface::create(file, w, h);
        auto context = Cairo::Context::create(surface);
        Graphics2D_cairo g2(context);
        if (!isTransparent(TRANSPARENT)) {
                g2.setColor(TRANSPARENT);
                g2.fillRect(0, 0, w, h);
        }
        r->draw(g2, 10, 10);
        delete r;
        return 0;
}
