dialog test {
    # root = "dialog.locale.dialog.test"
    # text = "start.first"
    nodes {
        _start {
            text = ["dialog.locale.dialog.test.start.first",
                "dialog.locale.dialog.test.start.second",
                "dialog.locale.dialog.test.start.third"]
            choices = [
                {
                    text = "dialog.locale.dialog.test.start.choices.next",
                    node = "core.dialog:dialog.test.next"
                }
            ]
        }
        next {
            text = "dialog.locale.dialog.test.next.text"
            choices = [
                {
                    text = "dialog.locale.dialog.test.next.choices.yes",
                    node = "core.dialog:dialog.test.yes"
                },
                {
                    text = "dialog.locale.dialog.test.next.choices.no",
                    node = "core.dialog:dialog.test.end"
                }
            ]
        }
        yes {
            text = "dialog.locale.dialog.test.yes.text"
            choices = [
                {
                    text = "more"
                    node = "core.dialog:dialog.test._start"
                }
            ]
        }
        end {
            text = "dialog.locale.dialog.test.end.text"

            choices = End
        }
    }
}
