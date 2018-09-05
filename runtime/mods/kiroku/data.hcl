data {
    define = ["test"]

    load {
        kiroku.test = ["data/test.hcl"]
        core.item = ["data/item.hcl"]
        core.item_chip = ["data/item_chip.hcl"]
    }
}
