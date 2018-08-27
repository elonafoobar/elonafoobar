locale {
    dialog {
        test {
            start {
                first = "こんにちは世界"
                second = "This is text."
                third = "This is more text."

                choices {
                    next = "Next."
                }
            }
            next {
                text = "What now?"

                choices {
                    yes = "Alright."
                    no = "No way!"
                }
            }
            yes {
                text = "Yes!"
            }
            end {
                text = "...Really?"
            }
        }

        redirect {
            one {
                text = "Picked first."
            }
            two {
                text = "Second was picked."
            }
        }
    }
}
