#include <SFML/Graphics.hpp>
#include <EditorView.h>
#include <TextDocument.h>
#include <InputController.h>
#include <ImplementationUtils.h>

int main() {
	std::string workingDirectory = ImplementationUtils::getWorkingDirectory("");

	std::string saveFileName;
	std::string loadFileName;

	saveFileName = "txt/textoDePruebaGuardado.txt";
	loadFileName = "txt/textoDePruebaGuardado.txt";

	sf::RenderWindow window(sf::VideoMode(720, 405), "Text Editor");
	window.setVerticalSyncEnabled(true);
	sf::Color backgroundColor = sf::Color(21, 29, 45);

	TextDocument document;
	document.init(loadFileName);

	EditorContent editorContent(document);

	EditorView editorView(window, workingDirectory, editorContent);
	InputController inputController(editorContent);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::Resized) {
				editorView.setCameraBounds(event.size.width, event.size.height);
			}
			if (event.key.code == sf::Keyboard::S && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
				if (document.hasChanged()) {
					document.saveFile(saveFileName);
					std::cout << "SAVED TO: " << saveFileName << "\n";
				}
			}

			inputController.handleEvents(editorView, window, event);
		}

		inputController.handleConstantInput(editorView, window);

		window.clear(backgroundColor);
		window.setView(editorView.getCameraView());
		editorView.draw(window);
		window.display();
	}

	return 0;
}