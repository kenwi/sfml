#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <cmath>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

	ParticleSystem(unsigned int count) 
		: particles(count)
		, vertices(sf::Points, count)
		, lifetime(sf::seconds(3.f))
		, emitter(0.f, 0.f)
	{
	}

	void setEmitter(sf::Vector2f position)
	{
		emitter = position;
	}

	void update(sf::Time deltaTime)
	{
		for (std::size_t i = 0; i < particles.size(); ++i)
		{
			Particle& p = particles[i];
			p.lifetime -= deltaTime;

			if (p.lifetime <= sf::Time::Zero)
				resetParticle(i);

			sf::Vector2f gravity(0.0, -9.81f);

			p.velocity.x += gravity.x*gravity.x / 1000;
			p.velocity.y += gravity.y*gravity.y / 1000;

			vertices[i].position += p.velocity * deltaTime.asSeconds();

			float ratio = p.lifetime.asSeconds() / lifetime.asSeconds();
			vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
		}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;
		target.draw(vertices, states);
	}

private:

	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};

	void resetParticle(std::size_t index)
	{
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 50) + 50.f;
		
		particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

		vertices[index].position = emitter;
	}

	std::vector<Particle> particles;
	sf::VertexArray vertices;
	sf::Time lifetime;
	sf::Vector2f emitter;
};