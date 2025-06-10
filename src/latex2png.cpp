#include "MicroTeX/platform/cairo/graphic_cairo.h"
#include "MicroTeX/latex.h"
#include <gtkmm.h>
#include <iostream>
#include <string>

using namespace tex;

class TexGuard {
public:
    TexGuard() {
        LaTeX::init();
    }

};

int generate_png(std::wstring& code, std::string& file) {
        TexGuard texGuard;
        std::cout << "Made it to l18\n";
        auto r = LaTeX::parse(code, 720, 20, 10, BLACK);
        std::cout << "Made it to l20\n";
        const float w = r->getWidth() + 11 * 2;
        std::cout << "Made it to l22\n";
        const float h = r->getHeight() + 11 * 2;
        std::cout << "Made it to l24\n";
        auto surface = Cairo::SvgSurface::create(file, w, h);
        std::cout << "Made it to l26\n";
        auto context = Cairo::Context::create(surface);
        std::cout << "Made it to l28\n";
        Graphics2D_cairo g2(context);
        std::cout << "Made it to l30\n";
        if (!isTransparent(TRANSPARENT)) {
        std::cout << "Made it to l32\n";
                g2.setColor(TRANSPARENT);
        std::cout << "Made it to l34\n";
                g2.fillRect(0, 0, w, h);
        std::cout << "Made it to l36\n";
        }
        r->draw(g2, 10, 10);
        std::cout << "Made it to l39\n";
        delete r;
        std::cout << "Made it to l41\n";
        return 0;
}
